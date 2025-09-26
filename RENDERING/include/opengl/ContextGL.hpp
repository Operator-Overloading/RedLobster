// RENDERING/include/opengl/ContextGL.hpp

#pragma once

#include "Context.hpp"

#include "PLATFORM/include/Window.hpp"

#ifdef ENGINE_PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace Lobster
{
	class LOBSTER_API ContextGL : public Context::RenderingContext
	{
	private:
#ifdef ENGINE_PLATFORM_WINDOWS
		struct Win32Types
		{
			HGLRC hrc;
			HDC hdc;
		};

		static Win32Types wctx;
#endif
	public:
		void Make(void* handle) override;
		void SwapBuffers() override;
	};
};