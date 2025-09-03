// CORE/src/Application.cpp

#pragma once
#include "Application.hpp"
#include "Logger.hpp"

namespace Lobster
{
	Application::Application()
	{
		window = new Win32Window{900,600,"lobsta"};
		window->SetEventCallbackFunction(std::bind(&Application::OnEvent,this,std::placeholders::_1));
	}
	
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		//Input::OnEvent(event);

		if(event.GetType() != EventTypeMouseMoved)
			Logger::Debug(event.ToString());

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

		while(is_running)
		{
			window->Update();

			if(!window->IsMinimized())
			{
				OnUpdate(0.0f);

				{
					for(Layer* layer : layer_stack) layer->OnUpdate(0.0f);
				}
			}

			is_running = !window->WindowShouldClose();
		}

		return 0;
	}
};