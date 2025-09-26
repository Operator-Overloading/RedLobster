// RENDERING/src/opengl/ContextGl.cpp

#include "opengl/ContextGL.hpp"

#include "Logger.hpp"
#include "Macros.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

namespace Lobster
{
	
#ifdef ENGINE_PLATFORM_WINDOWS
	ContextGL::Win32Types ContextGL::wctx;
#endif

	void ContextGL::Make(void* handle)
	{
		this->handle = handle;

#ifdef ENGINE_PLATFORM_WINDOWS
		HWND window = (HWND)handle;

		wctx.hdc = GetDC(window);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32, // color depth
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			24, // depth buffer
			8,  // stencil buffer
			0, 0, 0, 0, 0, 0
		};

		int pixelformat = ChoosePixelFormat(wctx.hdc,&pfd);

		SetPixelFormat(wctx.hdc,pixelformat,&pfd);

		wctx.hrc = wglCreateContext(wctx.hdc);

		wglMakeCurrent(wctx.hdc,wctx.hrc);

		lassert(gladLoadGL(),"Failed to load GLAD!");
#else
		lassert(gladLoadGL(),"Failed to load GLAD!");
#endif
	}

	void ContextGL::SwapBuffers()
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		::SwapBuffers(wctx.hdc);
#else
		glfwSwapBuffers();
#endif
	}
}