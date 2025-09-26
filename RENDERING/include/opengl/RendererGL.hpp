// RENDERING/include/opengl/RendererGL.hpp

#pragma once
#include "Renderer.hpp"

namespace Lobster
{
	class LOBSTER_API RendererGL : public Renderer
	{
	public:
		RendererGL();
		
		void Shutdown() override;

		void BeginFrame() override;
		void EndFrame() override;

		void Clear(float r,float g,float b,float a) override;

		void Resize(int width,int height) override;
	};
}