// RENDERING/src/Renderer.cpp

#include "Renderer.hpp"
#include "Context.hpp"

#include "Logger.hpp"
#include "Macros.hpp"

#include "opengl/RendererGL.hpp"

namespace Lobster
{
	std::shared_ptr<Renderer> Renderer::Create()
	{
		switch(Context::api)
		{
		case API::OPENGL:
		{
			return std::make_shared<RendererGL>();
		}
		default:
		{
			LOG_ERROR("Could not load the correct API!");

			return nullptr;
		}
		}
	}
}