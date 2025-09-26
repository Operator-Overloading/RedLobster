// RENDERING/include/Context.hpp

#pragma once

#include "Export.hpp"

#include "PLATFORM/include/Window.hpp"

namespace Lobster
{
	enum class LOBSTER_API API
	{
		OPENGL,
		VULKAN,
		DIRECTX,
	};

	class LOBSTER_API Context
	{
		friend class Renderer;
	public:
		class RenderingContext
		{
		protected:
			void* handle;
		public:
			virtual ~RenderingContext() = default;

			virtual void SwapBuffers() = 0;
			virtual void Make(void* handle) = 0;
		};
	private:
		static API api;
		static std::unique_ptr<RenderingContext> rc;
	public:
		static void UseOpenGL();
		static void UseVulkan();
		static void UseDirectX();
	public:
		static void CreateContext(Window* window);
		static void SwapBuffers();
	};
}