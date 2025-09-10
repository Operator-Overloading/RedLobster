// INPUT/src/MouseInputs.cpp

#include "MouseInputs.hpp"

#include <bitset>
#include <queue>

namespace Lobster
{
	namespace Input
	{
		static float x = 0.0f;
		static float y = 0.0f;

		static float prev_x = 0.0f;
		static float prev_y = 0.0f;

		static float scroll_delta_x = 0.0f;
		static float scroll_delta_y = 0.0f;

		static bool cursor_visible = true;
		static bool cursor_confined = false;
		static bool cursor_in_window = false;

		static std::bitset<16u> buttonstates;
		static std::bitset<16u> previousstates;

		static std::queue<Event*> mousebuffer;

		void TrimBuffer(std::queue<Event*> buffer)
		{
			while(buffer.size() > 127u)
			{
				buffer.pop();
			}
		}


		std::pair<float,float> GetMousePos()
		{
			return {x,y};
		}

		std::pair<float,float> GetMouseDelta()
		{
			return {x - prev_x,y - prev_y};
		}

		float GetMouseX()
		{
			return x;
		}

		float GetMouseY()
		{
			return y;
		}

		float GetMouseDeltaX()
		{
			return x - prev_x;
		}

		float GetMouseDeltaY()
		{
			return y - prev_y;
		}

		bool IsMouseInWindow()
		{
			return cursor_in_window;
		}

		bool IsMouseButtonDown(MouseCode button)
		{
			return buttonstates[button];
		}

		bool IsMouseButtonUp(MouseCode button)
		{
			return !buttonstates[button];
		}

		bool WasMouseButtonDown(MouseCode button)
		{
			return previousstates[button];
		}

		float GetScrollX()
		{
			return scroll_delta_x;
		}

		float GetScrollY()
		{
			return scroll_delta_y;
		}

		float GetScrollDelta()
		{
			return scroll_delta_y;
		}

		void SetCursorVisible(bool visible,Window* window)
		{
			cursor_visible = visible;
			window->SetCursorVisible(cursor_visible);
		}

		void SetCursorConfined(bool confined,Window* window)
		{
			cursor_confined = confined;
			window->SetCursorConfined(cursor_confined);
		}

		bool IsCursorVisible()
		{
			return cursor_visible;
		}

		bool IsCursorConfined()
		{
			return cursor_confined;
		}

		void MouseUpdate()
		{
			prev_x = x;
			prev_y = y;

			previousstates = buttonstates;

			scroll_delta_x = 0.0f;
			scroll_delta_y = 0.0f;
		}

		std::optional<Event*> ReadMouse()
		{
			if(mousebuffer.size() > 0u)
			{
				Event* e = mousebuffer.front();
				mousebuffer.pop();
				return e;
			}
			return {};
		}

		void OnMouseEvent(Event& event)
		{
			switch(event.GetType())
			{
			case EventTypeMouseMoved:
			{
				MouseMovedEvent& mme = (MouseMovedEvent&)event;
				x = mme.GetX();
				y = mme.GetY();

				mousebuffer.push(&event);
				TrimBuffer(mousebuffer);

				break;
			}
			case EventTypeMouseScrolled:
			{
				MouseScrolledEvent& mse = (MouseScrolledEvent&)event;
				scroll_delta_x += mse.GetX();
				scroll_delta_y += mse.GetY();

				mousebuffer.push(&event);
				TrimBuffer(mousebuffer);

				break;
			}
			case EventTypeMouseEntered:
			{
				cursor_in_window = true;

				mousebuffer.push(&event);
				TrimBuffer(mousebuffer);

				break;
			}
			case EventTypeMouseLeft:
			{
				cursor_in_window = false;

				mousebuffer.push(&event);
				TrimBuffer(mousebuffer);

				buttonstates.reset();

				break;
			}
			case EventTypeMouseClicked:
			{
				MouseClickedEvent& mce = (MouseClickedEvent&)event;
				buttonstates[mce.GetMouseButton()] = true;

				mousebuffer.push(&event);
				TrimBuffer(mousebuffer);

				break;
			}
			case EventTypeMouseReleased:
			{
				MouseReleasedEvent& mre = (MouseReleasedEvent&)event;
				buttonstates[mre.GetMouseButton()] = false;

				mousebuffer.push(&event);
				TrimBuffer(mousebuffer);

				break;
			}
			}
		}
	}
}