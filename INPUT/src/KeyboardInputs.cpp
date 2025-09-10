// INPUT/src/KeyboardInputs.cpp

#include "KeyboardInputs.hpp"

#include <bitset>
#include <queue>

namespace Lobster
{
	namespace Input
	{
		static bool autorepeat = false;

		static std::bitset<512u> keystates;
		static std::queue<char> charbuffer;
		static std::queue<KeyEvent*> keybuffer;

		void TrimBuffer(std::queue<char> buffer)
		{
			while(buffer.size() > 255u)
			{
				buffer.pop();
			}
		}

		void TrimBuffer(std::queue<KeyEvent*> buffer)
		{
			while(buffer.size() > 127u)
			{
				buffer.pop();
			}
		}

		bool IsKeyDown(KeyCode keycode)
		{
			return keystates[keycode];
		}

		bool IsKeyUp(KeyCode keycode)
		{
			return !keystates[keycode];
		}

		std::optional<char> ReadChar()
		{
			if(charbuffer.size() > 0)
			{
				char c = charbuffer.front();
				charbuffer.pop();
				return c;
			}
			return {};
		}

		std::optional<KeyEvent*> ReadKey()
		{
			if(keybuffer.size() > 0)
			{
				KeyEvent* k = keybuffer.front();
				keybuffer.pop();
				return k;
			}
			return {};
		}

		std::string DumpChars()
		{
			std::string res = "";

			while(charbuffer.size() > 0)
			{
				res += charbuffer.front();
				charbuffer.pop();
			}

			return res;
		}

		bool Autorepeat()
		{
			return autorepeat;
		}

		void DisableAutorepeat()
		{
			autorepeat = false;
		}

		void EnableAutorepeat()
		{
			autorepeat = true;
		}

		void ClearStates()
		{
			keystates.reset();
		}

		void Flush()
		{
			charbuffer = std::queue<char>();
		}

		void OnKeyEvent(KeyEvent& e)
		{
			switch(e.GetType())
			{
			case EventTypeKeyPressed:
			{
				keystates[e.GetKeyCode()] = true;

				keybuffer.push(&e);
				TrimBuffer(keybuffer);

				break;
			}
			case EventTypeKeyReleased:
			{
				keystates[e.GetKeyCode()] = false;

				keybuffer.push(&e);
				TrimBuffer(keybuffer);

				break;
			}
			case EventTypeKeyTyped:
			{
				charbuffer.push((char)e.GetKeyCode());
				TrimBuffer(charbuffer);

				break;
			}
			default:
				break;
			}
		}
	}
}