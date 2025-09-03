// CORE/include/ApplicationEvents.hpp

#pragma once
#include "Event.hpp"

#include <sstream>

namespace Lobster
{
	class LOBSTER_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width,unsigned int height) : _width(width),_height(height) {}

		unsigned int GetWidth() const { return _width; }
		unsigned int GetHeight() const { return _height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << _width << ", " << _height;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeWindowResized; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowResizeEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	private:
		unsigned int _width,_height;
	};

	class LOBSTER_API WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int x,int y) : _x(x),_y(y) {}

		int GetX() const { return _x; }
		int GetY() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMoveEvent: " << _x << ", " << _y;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeWindowMoved; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowMoveEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	private:
		int _x,_y;
	};

	class LOBSTER_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		std::string ToString() const override
		{
			return "WindowFocusEvent";
		}

		static EventType GetStaticType() { return EventType::EventTypeWindowFocus; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowFocusEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class LOBSTER_API WindowFocusLostEvent : public Event
	{
	public:
		WindowFocusLostEvent() = default;

		std::string ToString() const override
		{
			return "WindowFocusLostEvent";
		}

		static EventType GetStaticType() { return EventType::EventTypeWindowFocusLost; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowFocusLostEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class LOBSTER_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		std::string ToString() const override
		{
			return "WindowCloseEvent";
		}

		static EventType GetStaticType() { return EventType::EventTypeWindowClosed; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowCloseEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class LOBSTER_API GameTickEvent : public Event
	{
	public:
		GameTickEvent() = default;

		std::string ToString() const override
		{
			return "GameTickEvent";
		}

		static EventType GetStaticType() { return EventType::EventTypeGameTick; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "GameTickEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class LOBSTER_API GameUpdateEvent : public Event
	{
	public:
		GameUpdateEvent() = default;

		std::string ToString() const override
		{
			return "GameUpdateEvent";
		}

		static EventType GetStaticType() { return EventType::EventTypeGameUpdate; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "GameUpdateEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class LOBSTER_API GameRenderEvent : public Event
	{
	public:
		GameRenderEvent() = default;

		std::string ToString() const override
		{
			return "GameRenderEvent";
		}

		static EventType GetStaticType() { return EventType::EventTypeGameRender; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "GameRenderEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};
}