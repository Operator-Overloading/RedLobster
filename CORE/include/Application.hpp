// CORE/include/Application.hpp

#pragma once
#include "Export.hpp"
#include "Layer.hpp"
#include "Event.hpp"
#include "PLATFORM/include/windows/Win32Window.hpp"

namespace Lobster
{
	class LOBSTER_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		virtual void OnStart() = 0;
		virtual void OnUpdate(float dt) = 0;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Event& event);

		int Run();
	protected:
		bool is_running = false;
		Win32Window* window;
		LayerStack layer_stack;
	};
}