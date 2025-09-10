// INPUT/include/KeyboardEvents.hpp

#pragma once
#include "KeyCode.hpp"
#include "Event.hpp"

#include <sstream>

namespace Lobster
{
	class LOBSTER_API KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return _keycode; }

		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; }
	protected:
		KeyEvent(const KeyCode keycode) : _keycode(keycode) {}


		KeyCode _keycode;
	};

	class LOBSTER_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode,bool isRepeat = false) : KeyEvent(keycode),_is_repeat(isRepeat) {}

		bool IsRepeat() const { return _is_repeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _keycode << " [" << (char)_keycode << "] " << " (repeat = " << _is_repeat << ")";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeKeyPressed; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressedEvent"; }
	private:
		bool _is_repeat;
	};

	class LOBSTER_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _keycode << " [" << (char)_keycode << "] ";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeKeyReleased; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleasedEvent"; }
	};

	class LOBSTER_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << _keycode << " [" << (char)_keycode << "] ";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::EventTypeKeyTyped; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyTypedEvent"; }
	};
}