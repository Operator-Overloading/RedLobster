// PLATFORM/src/windows/Win32Window.cpp

#include "windows/Win32Window.hpp"
#include "resource.h"

#include "INPUT/include/KeyCode.hpp"
#include "INPUT/include/MouseEvents.hpp"
#include "INPUT/include/KeyboardEvents.hpp"

#include "CORE/include/ApplicationEvents.hpp"
#include "CORE/include/Logger.hpp"
#include "CORE/include/Macros.hpp"

namespace Lobster
{
	Win32Window::WindowClass Win32Window::WindowClass::wnd_class;

	Win32Window::WindowClass::WindowClass() : instance(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wc = {0};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = static_cast<HICON>(LoadImage(GetInstance(),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));
		wc.hCursor = 0;
		wc.hbrBackground = 0;
		wc.lpszMenuName = 0;
		wc.lpszClassName = GetName();
		wc.hIconSm = static_cast<HICON>(LoadImage(GetInstance(),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,16,16,0));

		RegisterClassEx(&wc);
	}

	Win32Window::WindowClass::~WindowClass()
	{
		UnregisterClass(wnd_class_name,GetInstance());
	}

	const char* Win32Window::WindowClass::GetName()
	{
		return wnd_class_name;
	}

	HINSTANCE Win32Window::WindowClass::GetInstance()
	{
		return wnd_class.instance;
	}

	Win32Window::Win32Window(int width,int height,const char* title)
	{
		this->width = width;
		this->height = height;
		this->title = title;

		RECT wr;
		wr.left = 100;
		wr.right = width + wr.left;
		wr.top = 100;
		wr.bottom = height + wr.top;

		lassert(AdjustWindowRect(&wr,WS_CAPTION|WS_OVERLAPPEDWINDOW|WS_SYSMENU,FALSE),"Failed to adjust window rect!");

		handle = CreateWindow(WindowClass::GetName(),title,WS_CAPTION|WS_OVERLAPPEDWINDOW|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,wr.right - wr.left,wr.bottom - wr.top,0,0,WindowClass::GetInstance(),this);

		lassert(handle != nullptr,"Failed to create window!");

		ShowWindow(handle,SW_SHOWDEFAULT);

		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = 0;
		lassert(RegisterRawInputDevices(&rid,1,sizeof(rid)),"Failed to register raw input device!");
	}

	Win32Window::~Win32Window()
	{
		DestroyWindow(handle);
	}

	void Win32Window::SetWidth(int width)
	{
	}

	void Win32Window::SetHeight(int height)
	{
	}

	void Win32Window::SetMinimized(bool minimized)
	{
	}

	void Win32Window::SetFocused(bool focused)
	{
	}

	void Win32Window::SetTitle(const std::string& title)
	{
		this->title = title.c_str();;
		SetWindowText(handle,this->title);
	}

	void Win32Window::SetCursorEnabled(bool enabled)
	{
		cursor_enabled = enabled;
		
		if(enabled)
		{
			while(::ShowCursor(1) < 0);
			ClipCursor(0);
		}
		else
		{
			while(::ShowCursor(0) >= 0);
			RECT rect;
			GetClientRect(handle,&rect);
			MapWindowPoints(handle,0,reinterpret_cast<POINT*>(&rect),2);
			ClipCursor(&rect);
		}
	}

	void Win32Window::Update()
	{
		const auto ecode = ProcessMessages();

		if(ecode == WM_QUIT)
		{
		}
	}

	int Win32Window::GetWidth() const
	{
		return width;
	}

	int Win32Window::GetHeight() const
	{
		return height;
	}

	std::string Win32Window::GetTitle() const
	{
		return title;
	}

	bool Win32Window::IsMinimized() const
	{
		return minimized;
	}

	bool Win32Window::IsFocused() const
	{
		return focused;
	}

	bool Win32Window::IsCursorEnabled() const
	{
		return cursor_enabled;
	}

	bool Win32Window::WindowShouldClose() const
	{
		return should_close;
	}

	void* Win32Window::GetHandle()
	{
		return handle;
	}

	std::optional<int> Win32Window::ProcessMessages()
	{
		MSG msg;

		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				return (int)msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return {};
	}

	LRESULT __stdcall Win32Window::HandleMsgSetup(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
	{
		if(msg == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);

			Win32Window* const pwnd = static_cast<Win32Window*>(pCreate->lpCreateParams);

			SetWindowLongPtr(hwnd,GWLP_USERDATA,reinterpret_cast<LONG_PTR>(pwnd));
			SetWindowLongPtr(hwnd,GWLP_WNDPROC,reinterpret_cast<LONG_PTR>(&Win32Window::HandleMsgThunk));

			return pwnd->HandleMsg(hwnd,msg,wparam,lparam);
		}

		return DefWindowProc(hwnd,msg,wparam,lparam);
	}
	
	LRESULT __stdcall Win32Window::HandleMsgThunk(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
	{
		Win32Window* const pwnd = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd,GWLP_USERDATA));
		return pwnd->HandleMsg(hwnd,msg,wparam,lparam);
	}
	
	LRESULT Win32Window::HandleMsg(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
	{
		//if(ImGui_ImplWin32_WndProcHandler(hwnd,msg,wparam,lparam))
			//return true;
		//const auto& imio = ImGui::GetIO();
		
		switch(msg)
		{
		case WM_CLOSE:
		{
			WindowCloseEvent closeevent{};
			this->event_callback(closeevent);

			should_close = true;
			PostQuitMessage(0);
			return 0;
		}
		case WM_ACTIVATE:
		{
			break;
		}
		case WM_MOVE:
		{
			const POINTS pt = MAKEPOINTS(lparam);

			WindowMoveEvent windowmove((short)(pt.x),(short)(pt.y));
			if(this->event_callback != nullptr)
				this->event_callback(windowmove);
			break;
		}
		case WM_SIZE:
		{
			const POINTS pt = MAKEPOINTS(lparam);

			WindowResizeEvent windowresize(pt.x,pt.y);
			if(this->event_callback != nullptr)
				this->event_callback(windowresize);
			break;
		}
		case WM_SETFOCUS:
		{
			WindowFocusEvent focusgained{};
			if(this->event_callback != nullptr)
				this->event_callback(focusgained);
			break;
		}
		case WM_KILLFOCUS:
		{
			WindowFocusLostEvent focuslost{};
			this->event_callback(focuslost);
			//kbd.Clear();
			break;
		}
	
		/*********** KEYBOARD MESSAGES ***********/
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			//if(imio.WantCaptureKeyboard)
			//{
				//break;
			//}
			if(!(lparam & 0x40000000))
			{
				KeyPressedEvent keypressedevent(static_cast<unsigned short>(wparam));
				this->event_callback(keypressedevent);
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			//if(imio.WantCaptureKeyboard)
			//{
				//break;
			//}
			KeyReleasedEvent keyreleasedevent(static_cast<unsigned short>(wparam));
			this->event_callback(keyreleasedevent);
			break;
		}
		case WM_CHAR:
		{
			//if(imio.WantCaptureKeyboard)
			//{
				//break;
			//}
			KeyTypedEvent keytypedevent(static_cast<unsigned short>(wparam));
			this->event_callback(keytypedevent);
			break;
		}
		/*********** END KEYBOARD MESSAGES ***********/
	
		/************* MOUSE MESSAGES ****************/
		case WM_MOUSEMOVE:
		{
			const POINTS pt = MAKEPOINTS(lparam);

			if(!cursor_enabled)
			{
				break;
			}

			//if(imio.WantCaptureMouse)
			//{
				//break;
			//}

			MouseMovedEvent mousemove((float)pt.x,(float)pt.y);
			this->event_callback(mousemove);

			TRACKMOUSEEVENT tme={};
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE|TME_HOVER;
            tme.hwndTrack = hwnd;
			tme.dwHoverTime = 1;

            TrackMouseEvent(&tme);

			break;
		}
		case WM_MOUSELEAVE:
		{
			if(cursor_in_window)
			{
				MouseLeftEvent leave{};
				this->event_callback(leave);

				cursor_in_window = false;
			}
			break;
		}
		case WM_MOUSEHOVER:
		{
			if(!cursor_in_window)
			{
				MouseEnteredEvent enter{};
				this->event_callback(enter);

				cursor_in_window = true;
			}

			break;
		}
		case WM_MOUSEWHEEL:
		{
			//if(imio.WantCaptureMouse)
			//{
				//break;
			//}
			const POINTS pt = MAKEPOINTS(lparam);
			const int delta = GET_WHEEL_DELTA_WPARAM(wparam);
			//mouse.OnWheelDelta((float)pt.x,(float)pt.y,(float)delta);
			MouseScrolledEvent rawscroll((float)delta,0);
			this->event_callback(rawscroll);
			break;
		}
		case WM_MOUSEHWHEEL:
		{
			//if(imio.WantCaptureMouse)
			//{
				//break;
			//}
			const POINTS pt = MAKEPOINTS(lparam);
			const int delta = GET_WHEEL_DELTA_WPARAM(wparam);
			//mouse.OnWheelDelta((float)pt.x,(float)pt.y,(float)delta);
			MouseScrolledEvent rawscroll(0,(float)delta);
			this->event_callback(rawscroll);
			break;
		}
		/************** END MOUSE MESSAGES **************/
		
		/************** RAW MOUSE MESSAGES **************/
		case WM_INPUT:
		{
			//if(!mouse.RawEnabled())
			//{
				//break;
			//}
			UINT size = 0;

			if(GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam),RID_INPUT,0,&size,sizeof(RAWINPUTHEADER))==-1)
			{
				break;
			}

			raw_buffer.resize(size);

			if(GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam),RID_INPUT,raw_buffer.data(),&size,sizeof(RAWINPUTHEADER))!=size)
			{
				break;
			}

			auto& ri = reinterpret_cast<const RAWINPUT&>(*raw_buffer.data());
			if(ri.header.dwType == RIM_TYPEMOUSE)
			{
				switch(ri.data.mouse.usButtonFlags)
				{
				case RI_MOUSE_BUTTON_1_DOWN:
				{
					MouseClickedEvent b1pressed(MouseButton::b0);
					this->event_callback(b1pressed);
					break;
				}
				case RI_MOUSE_BUTTON_1_UP:
				{
					MouseReleasedEvent b1release(MouseButton::b0);
					this->event_callback(b1release);
					break;
				}
				case RI_MOUSE_BUTTON_2_DOWN:
				{
					MouseClickedEvent b2pressed(MouseButton::b1);
					this->event_callback(b2pressed);
					break;
				}
				case RI_MOUSE_BUTTON_2_UP:
				{
					MouseReleasedEvent b2release(MouseButton::b1);
					this->event_callback(b2release);
					break;
				}
				case RI_MOUSE_BUTTON_3_DOWN:
				{
					MouseClickedEvent b3pressed(MouseButton::b2);
					this->event_callback(b3pressed);
					break;
				}
				case RI_MOUSE_BUTTON_3_UP:
				{
					MouseReleasedEvent b3release(MouseButton::b2);
					this->event_callback(b3release);
					break;
				}
				case RI_MOUSE_BUTTON_4_DOWN:
				{
					MouseClickedEvent b4pressed(MouseButton::b3);
					this->event_callback(b4pressed);
					break;
				}
				case RI_MOUSE_BUTTON_4_UP:
				{
					MouseReleasedEvent b4release(MouseButton::b3);
					this->event_callback(b4release);
					break;
				}
				case RI_MOUSE_BUTTON_5_DOWN:
				{
					MouseClickedEvent b5pressed(MouseButton::b4);
					this->event_callback(b5pressed);
					break;
				}
				case RI_MOUSE_BUTTON_5_UP:
				{
					MouseReleasedEvent b5release(MouseButton::b4);
					this->event_callback(b5release);
					break;
				}
				default:
					break;
				}
				break;
			}

			break;
		}
		/************** END RAW MOUSE MESSAGES **************/
		}

		return DefWindowProc(hwnd,msg,wparam,lparam);
	}
}