// PLATFORM/src/windows/Win32Window.cpp

#include "windows/Win32Window.hpp"

#include "INPUT/include/Input.hpp"

#include "CORE/include/ApplicationEvents.hpp"
#include "CORE/include/Logger.hpp"
#include "CORE/include/Macros.hpp"

namespace Lobster
{
	Win32Window::WindowClass Win32Window::WindowClass::wnd_class;

	Win32Window::WindowClass::WindowClass() : instance(GetModuleHandle(0))
	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = static_cast<HICON>(LoadImage(GetInstance(),MAKEINTRESOURCE(101),IMAGE_ICON,32,32,0));
		wc.hCursor = 0;
		wc.hbrBackground = 0;
		wc.lpszMenuName = 0;
		wc.lpszClassName = GetName();
		wc.hIconSm = static_cast<HICON>(LoadImage(GetInstance(),MAKEINTRESOURCE(101),IMAGE_ICON,16,16,0));

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

	void Win32Window::SetTitle(const std::string& title)
	{
		this->title = title.c_str();;
		SetWindowText(handle,this->title);
	}

	void Win32Window::SetCursorConfined(bool confined)
	{
		if(confined)
		{
			RECT rect;
			GetClientRect(handle,&rect);
			MapWindowPoints(handle,0,reinterpret_cast<POINT*>(&rect),2);
			ClipCursor(&rect);
		}
		else
		{
			ClipCursor(0);
		}
	}

	void Win32Window::SetCursorVisible(bool visible)
	{
		if(visible)
		{
			while(::ShowCursor(1) < 0);
		}
		else
		{
			while(::ShowCursor(0) >= 0);
		}
	}

	void Win32Window::SetCursorEnabled(bool enabled)
	{
		cursor_enabled = enabled;
		
		if(enabled)
		{
			SetCursorVisible(true);
			SetCursorConfined(false);
		}
		else
		{
			SetCursorVisible(false);
			SetCursorConfined(true);
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

			WindowMoveEvent windowmove((int)(pt.x),(int)(pt.y));
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
			focused = true;
			minimized = false;
			break;
		}
		case WM_KILLFOCUS:
		{
			const POINTS pt = MAKEPOINTS(lparam);

			WindowFocusLostEvent focuslost{};
			this->event_callback(focuslost);

			MouseLeftEvent leave{(float)pt.x,(float)pt.y};
			this->event_callback(leave);

			focused = false;
			Input::ClearStates();
			break;
		}
		case WM_SYSCOMMAND:
		{
			if((wparam & 0xFFF0) == 0xF020) // On Minimize
			{
				minimized = true;
			}
			if((wparam & 0xFFF0) == 0xF030) // On Maximize
			{
				minimized = false;
			}
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
			if(!(lparam & 0x40000000) || Input::Autorepeat())
			{
				KeyPressedEvent keypressedevent(Win32ToGlfwKey(wparam));
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
			KeyReleasedEvent keyreleasedevent(Win32ToGlfwKey(wparam));
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

			MouseMovedEvent mousemove{(float)pt.x,(float)pt.y};
			this->event_callback(mousemove);

			TRACKMOUSEEVENT tme={};
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE|TME_HOVER;
            tme.hwndTrack = hwnd;
			tme.dwHoverTime = 1;

            TrackMouseEvent(&tme);

			break;
		}
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_XBUTTONDOWN:
		{
			// 513, 519, 516
			// This is the most retarded ternary operator I've ever written, I should've just put this in the if/else statement. Oh well
			MouseCode button = (msg == WM_XBUTTONDOWN) ? GET_XBUTTON_WPARAM(wparam) + 2 : ((msg / 3u) - 171);
			MouseClickedEvent mousepress(button);
			this->event_callback(mousepress);

			break;
		}
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_XBUTTONUP:
		{
			MouseCode button = (msg == WM_XBUTTONUP) ? GET_XBUTTON_WPARAM(wparam) + 2 : ((msg / 3u) - 171);
			MouseReleasedEvent mouserelease(button);
			this->event_callback(mouserelease);

			break;
		}
		case WM_MOUSELEAVE:
		{
			if(cursor_in_window)
			{
				const POINTS pt = MAKEPOINTS(lparam);

				MouseLeftEvent leave{(float)pt.x,(float)pt.y};
				this->event_callback(leave);

				cursor_in_window = false;
			}
			break;
		}
		case WM_MOUSEHOVER:
		{
			if(!cursor_in_window)
			{
				const POINTS pt = MAKEPOINTS(lparam);

				MouseEnteredEvent enter{(float)pt.x,(float)pt.y};
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
			const float delta = GET_WHEEL_DELTA_WPARAM(wparam) / float(WHEEL_DELTA);
			//mouse.OnWheelDelta((float)pt.x,(float)pt.y,(float)delta);
			MouseScrolledEvent rawscroll(0,delta);
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
			const float delta = GET_WHEEL_DELTA_WPARAM(wparam) / float(WHEEL_DELTA);
			//mouse.OnWheelDelta((float)pt.x,(float)pt.y,(float)delta);
			MouseScrolledEvent rawscroll(delta,0);
			this->event_callback(rawscroll);
			break;
		}
		/************** END MOUSE MESSAGES **************/
		
		/************** RAW MOUSE MESSAGES **************/
		case WM_INPUT:
		{
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
				break;
			}

			break;
		}
		/************** END RAW MOUSE MESSAGES **************/
		}

		return DefWindowProc(hwnd,msg,wparam,lparam);
	}
}