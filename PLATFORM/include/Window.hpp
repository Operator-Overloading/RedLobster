// PLATFORM/include/Window.hpp

#pragma once
#include "Event.hpp"

#include <string>
#include <functional>

namespace Lobster
{
	class Window
	{
		using EventFn = std::function<void(Event&)>;
	public:
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual bool IsMinimized() const = 0;
		virtual bool IsFocused() const = 0;
		virtual bool IsCursorEnabled() const = 0;
		virtual bool WindowShouldClose() const = 0;
		virtual std::string GetTitle() const = 0;

		virtual void SetCursorConfined(bool b) = 0;
		virtual void SetCursorVisible(bool b) = 0;
		virtual void SetCursorEnabled(bool b) = 0;
		virtual void SetTitle(const std::string& title) = 0;

		virtual void* GetHandle() = 0;

		void SetEventCallbackFunction(const EventFn& fn) { this->event_callback = fn; };
	public:
		EventFn event_callback;
	};
}