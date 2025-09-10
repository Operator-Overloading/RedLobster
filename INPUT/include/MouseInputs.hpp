// INPUT/include/MouseInputs.hpp

#pragma once

#include "MouseEvents.hpp"

#include "PLATFORM/include/Window.hpp"

#include <utility>
#include <optional>

namespace Lobster
{
	namespace Input
	{
		LOBSTER_API std::pair<float,float> GetMousePos();
		LOBSTER_API std::pair<float,float> GetMouseDelta();
		LOBSTER_API float GetMouseX();
		LOBSTER_API float GetMouseY();
		LOBSTER_API float GetMouseDeltaX();
		LOBSTER_API float GetMouseDeltaY();

		LOBSTER_API bool IsMouseInWindow();
		LOBSTER_API bool IsMouseButtonDown(MouseCode button);
		LOBSTER_API bool IsMouseButtonUp(MouseCode button);
		LOBSTER_API bool WasMouseButtonDown(MouseCode button);

		LOBSTER_API float GetScrollX();
		LOBSTER_API float GetScrollY();
		LOBSTER_API float GetScrollDelta();

		LOBSTER_API void SetCursorVisible(bool visible,Window* window);
		LOBSTER_API void SetCursorConfined(bool confined,Window* window);
		LOBSTER_API bool IsCursorVisible();
		LOBSTER_API bool IsCursorConfined();

		LOBSTER_API void MouseUpdate();

		LOBSTER_API std::optional<Event*> ReadMouse();

		LOBSTER_API void OnMouseEvent(Event& event);
	}
}