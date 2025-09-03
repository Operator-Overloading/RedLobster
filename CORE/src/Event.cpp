// CORE/src/Event.cpp

#include "Event.hpp"

namespace Lobster
{
	EventDispatcher::EventDispatcher(Event& event) : event(event) {}

	template<typename T>
	bool EventDispatcher::Dispatch(EventFn<T> func)
	{
		if(event.GetType() == T::GetStaticType())
		{
			event.handled |= func(*(T*)&event);
			return true;
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& os,const Event& e)
	{
		return os << e.ToString();
	}
}