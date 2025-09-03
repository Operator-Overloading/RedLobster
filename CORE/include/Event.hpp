// CORE/include/Event.hpp

#pragma once
#include "Export.hpp"

#include <functional>
#include <string>
#include <ostream>

namespace Lobster
{
	enum LOBSTER_API EventType : unsigned int
	{
		EventTypeCustom = 0,
		EventTypeGameGeneric = 10, EventTypeGameTick = 2, EventTypeGameUpdate = 3, EventTypeGameRender = 4,
		EventTypeKeyGeneric = 10, EventTypeKeyPressed = 11, EventTypeKeyReleased = 12, EventTypeKeyTyped = 13,
		EventTypeMouseGeneric = 20, EventTypeMouseMoved = 21, EventTypeMouseClicked = 22, EventTypeMouseReleased = 23, EventTypeMouseScrolled = 24, EventTypeMouseLeft = 25, EventTypeMouseEntered = 26,
		EventTypeWindowGeneric = 30, EventTypeWindowClosed = 31, EventTypeWindowFocus = 32, EventTypeWindowFocusLost = 33, EventTypeWindowResized = 34, EventTypeWindowMoved = 35,
	};

	enum LOBSTER_API EventCategory : int
	{
		EventCategoryCustom        = 0,
		EventCategoryApplication   = 1 << 0,
		EventCategoryInput         = 1 << 1,
		EventCategoryKeyboard      = 1 << 2,
		EventCategoryMouse         = 1 << 3,
		EventCategoryMouseButton   = 1 << 4,
	};

	class LOBSTER_API Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }

		inline bool IsConsumed() { return handled; }
		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	protected:
		bool handled = false;
	};

	class LOBSTER_API EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event);

		template<typename T>
		bool Dispatch(EventFn<T> func);
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os,const Event& e);
}