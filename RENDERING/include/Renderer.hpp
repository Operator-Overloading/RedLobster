// RENDERING/include/Renderer.hpp

#pragma once
#include "Export.hpp"

#include <memory>

namespace Lobster
{
	class LOBSTER_API Renderer
	{
	protected:
		struct Settings
		{
			bool vsync = 1;

			int drawmode;

		} settings;
	public:
		static std::shared_ptr<Renderer> Create();

		virtual void Shutdown() = 0;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void Clear(float r,float g,float b,float a) = 0;

		virtual void Resize(int width,int height) = 0;
	};
}