// INPUT/include/MouseEvents.hpp

#pragma once
#include "KeyCode.hpp"
#include "Event.hpp"

#include <sstream>

namespace Lobster
{
	class LOBSTER_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x,const float y) : _x(x),_y(y) {}
		std::pair<float,float> GetPos() const { return {_x,_y}; }
		float GetX() const { return _x; }
		float GetY() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeMouseMoved; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMovedEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }
	private:
		float _x,_y;
	};

	class LOBSTER_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float x,const float y) : _x(x),_y(y) {}
		std::pair<float,float> GetPos() const { return {_x,_y}; }
		float GetX() const { return _x; }
		float GetY() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeMouseScrolled; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseScrolledEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }
	private:
		float _x,_y;
	};

	class LOBSTER_API MouseLeftEvent : public Event
	{
	public:
		MouseLeftEvent() : _in(false) {}
		bool IsInWindow() { return _in; }

		static EventType GetStaticType() { return EventType::EventTypeMouseLeft; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseLeftEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }
	private:
		bool _in = false;
	};

	class LOBSTER_API MouseEnteredEvent : public Event
	{
	public:
		MouseEnteredEvent() : _in(true) {}
		bool IsInWindow() { return _in; }

		static EventType GetStaticType() { return EventType::EventTypeMouseEntered; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseEnteredEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }
	private:
		bool _in = true;
	};

	class LOBSTER_API MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return _button; }
	protected:
		MouseButtonEvent(const MouseCode button) : _button(button) {}

		MouseCode _button;

		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }
	};

	class LOBSTER_API MouseClickedEvent : public MouseButtonEvent
	{
	public:
		MouseClickedEvent(const MouseCode button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseClickedEvent: " << _button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeMouseClicked; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseClickedEvent"; }
	};

	class LOBSTER_API MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleasedEvent: " << _button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeMouseReleased; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseReleasedEvent"; }
	};
}