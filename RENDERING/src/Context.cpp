// RENDERING/src/Context.cpp

#include "Context.hpp"

#include "opengl/ContextGL.hpp"

namespace Lobster
{
    API Context::api = API::OPENGL;
    std::unique_ptr<Context::RenderingContext> Context::rc;

    void Context::UseOpenGL()
    {
        api = API::OPENGL;
    }

    void Context::UseVulkan()
    {
        api = API::VULKAN;
    }

    void Context::UseDirectX()
    {
        api = API::DIRECTX;
    }

    void Context::CreateContext(Window* window)
    {
        switch(api)
        {
        case Lobster::API::OPENGL:
            rc = std::make_unique<ContextGL>();
            rc->Make(window->GetHandle());
            break;
        case Lobster::API::VULKAN:
            break;
        case Lobster::API::DIRECTX:
            break;
        default:
            return;
        }
    }

    void Context::SwapBuffers()
    {
        switch(api)
        {
        case Lobster::API::OPENGL:
            rc->SwapBuffers();
            break;
        case Lobster::API::VULKAN:
            break;
        case Lobster::API::DIRECTX:
            break;
        default:
            return;
        }
    }
}