// PLATFORM/src/opengl/OpenGLWindow.cpp

#include "opengl/OpenGLWindow.hpp"

#include "Logger.hpp"
#include "Macros.hpp"

#include "CORE/include/ApplicationEvents.hpp"

#include "INPUT/include/MouseEvents.hpp"
#include "INPUT/include/KeyboardEvents.hpp"
#include "INPUT/include/Input.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <imgui/imgui.h>

namespace Lobster
{
	OpenGLWindow::OpenGLWindow(int width,int height,const char* title) :  width(width),height(height),title(title)
	{
		lassert(glfwInit(),"Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width,height,title,0,0);

		if(!window)
		{
			Logger::Error("Failed to create window!");
			glfwTerminate();
		}

		handle = glfwGetWin32Window(window);

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window,this);

		SetWindowIcon(BUILD_PATH "icon1.png");

		glfwSetWindowSizeCallback(window,[](GLFWwindow* window,int width,int height)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);
			_window.width = width;
			_window.height = height;

			WindowResizeEvent event(width,height);
			_window.event_callback(event);
		});

		glfwSetWindowMaximizeCallback(window,[](GLFWwindow* window,int maximized)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			if(maximized == 1)
			{
				_window.minimized = false;
			}
			else
			{
				_window.minimized = true;
			}
		});

		glfwSetWindowPosCallback(window,[](GLFWwindow* window,int pos_x,int pos_y)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			WindowMoveEvent event(pos_x,pos_y);
			_window.event_callback(event);
		});

		glfwSetWindowFocusCallback(window,[](GLFWwindow* window,int focused)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			if(focused == 1)
			{
				WindowFocusEvent event;
				_window.focused = true;
				_window.event_callback(event);
			}
			else
			{
				WindowFocusLostEvent event;
				_window.focused = false;
				_window.event_callback(event);
			}
		});

		glfwSetWindowCloseCallback(window,[](GLFWwindow* window)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			_window.event_callback(event);
		});

		glfwSetKeyCallback(window,[](GLFWwindow* window,int key,int scancode,int action,int mods)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key,false);
					_window.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					_window.event_callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key,true);
					_window.event_callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(window,[](GLFWwindow* window,unsigned int keycode)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			_window.event_callback(event);
		});

		glfwSetMouseButtonCallback(window,[](GLFWwindow* window,int button,int action,int mods)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);
			
			switch(action)
			{
				case GLFW_PRESS:
				{
					MouseClickedEvent event(button);
					_window.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					_window.event_callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window,[](GLFWwindow* window,double offset_x,double offset_y)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)offset_x,(float)offset_y);
			_window.event_callback(event);
		});

		glfwSetCursorPosCallback(window,[](GLFWwindow* window,double pos_x,double pos_y)
		{
			OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)pos_x,(float)pos_y);
			_window.event_callback(event);
		});

		glfwSetCursorEnterCallback(window,[](GLFWwindow* window,int entered)
		{
			if(entered == GLFW_TRUE)
			{
				OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);
				
				MouseEnteredEvent event{0,0};
				_window.event_callback(event);
			}
			else
			{
				OpenGLWindow& _window = *(OpenGLWindow*)glfwGetWindowUserPointer(window);
				
				MouseLeftEvent event{0,0};
				_window.event_callback(event);
			}
		});
	}

	OpenGLWindow::~OpenGLWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void OpenGLWindow::Update()
	{
		glfwPollEvents();
	}

	void OpenGLWindow::SetWindowIcon(const char* path)
	{
		if(path)
		{
			int width,height,channels;
			unsigned char* data = stbi_load(path,&width,&height,&channels,4);
			
			if(data)
			{
				GLFWimage icon;
				icon.width = width;
				icon.height = height;
				icon.pixels = data;
				
				glfwSetWindowIcon(window,1,&icon);
				stbi_image_free(data);
				return;
			}
		}

		// Fallback
		const int size = 32;
		std::vector<unsigned char> pixels(size * size * 4);

		for(int y = 0; y < size; ++y)
		{
			for(int x = 0; x < size; ++x)
			{
				int index = (y * size + x) * 4;
				// Create a blue circle
				float dx = x - size/2.0f;
				float dy = y - size/2.0f;
				float dist = sqrt(dx*dx + dy*dy);
				
				if(dist < size/2.0f)
				{
					pixels[index] = 255;     // R
					pixels[index + 1] = 0;   // G
					pixels[index + 2] = 0;   // B
					pixels[index + 3] = 255; // A
				}
				else
				{
					pixels[index] = 0;       // R
					pixels[index + 1] = 0;   // G
					pixels[index + 2] = 0;   // B
					pixels[index + 3] = 0;   // A (transparent)
				}
			}
		}

		GLFWimage icon;
		icon.width = size;
		icon.height = size;
		icon.pixels = pixels.data();

		glfwSetWindowIcon(window,1,&icon);
	}

	int OpenGLWindow::GetWidth() const
	{
		return width;
	}

	int OpenGLWindow::GetHeight() const
	{
		return height;
	}

	std::string OpenGLWindow::GetTitle() const
	{
		return title;
	}

	bool OpenGLWindow::IsMinimized() const
	{
		return minimized;
	}

	bool OpenGLWindow::IsFocused() const
	{
		return focused;
	}

	bool OpenGLWindow::IsCursorEnabled() const
	{
		return cursor_enabled;
	}

	bool OpenGLWindow::WindowShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void* OpenGLWindow::GetHandle()
	{
		return handle;
	}

	void OpenGLWindow::SetTitle(const std::string& title)
	{
		this->title = title.c_str();
		glfwSetWindowTitle(window,title.c_str());
	}

	void OpenGLWindow::SetCursorConfined(bool confined)
	{
		if(confined)
		{
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_CAPTURED);
		}
		else
		{
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		}
	}

	void OpenGLWindow::SetCursorVisible(bool visible)
	{
		if(visible)
		{
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
		}
	}

	void OpenGLWindow::SetCursorEnabled(bool enabled)
	{
		if(enabled)
		{
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
			glfwSetCursorPos(window,width/2,height/2);
		}
		else
		{
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
			glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_CAPTURED);
		}
	}
}