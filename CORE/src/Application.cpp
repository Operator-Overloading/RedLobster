// CORE/src/Application.cpp

#pragma once
#include "Application.hpp"
#include "Logger.hpp"
#include "Macros.hpp"

#include "RENDERING/include/Context.hpp"
#include "RENDERING/include/Renderer.hpp"

namespace Lobster
{
	Application::Application()
	{
		window = new Win32Window(800,600,"lobsta");
		window->SetEventCallbackFunction(std::bind(&Application::OnEvent,this,std::placeholders::_1));

		Context::CreateContext(window);

		renderer = Renderer::Create();
	}
	
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		if(event.GetCategoryFlags() == (EventCategoryInput | EventCategoryKeyboard))
		{
			KeyEvent& k = (KeyEvent&)event;

			Input::OnKeyEvent(k);
		}

		Input::OnMouseEvent(event);

		for(auto it = layer_stack.rbegin(); it != layer_stack.rend(); ++it)
		{
			if(event.IsConsumed())
				break;

			(*it)->OnEvent(event);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layer_stack.PushOverlay(overlay);
	}
	

	int Application::Run()
	{
		is_running = true;

		OnStart();

		Input::Init();

		while(is_running)
		{
			Input::MouseUpdate();

			window->Update();

			if(!window->IsMinimized())
			{
				OnUpdate(0.0f);

				{
					renderer->Clear(0.24f,0.08f,0.12f,1.0f);

					Context::SwapBuffers();
				}

				{
					for(Layer* layer : layer_stack) layer->OnUpdate(0.0f);
				}
			}

			is_running = !window->WindowShouldClose();
		}

		return 0;
	}
};