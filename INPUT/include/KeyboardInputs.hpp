// INPUT/include/KeyboardInputs.hpp

#pragma once

#include "KeyboardEvents.hpp"

#include <optional>

namespace Lobster
{
	namespace Input
	{
		LOBSTER_API bool IsKeyDown(KeyCode keycode);
		LOBSTER_API bool IsKeyUp(KeyCode keycode);

		LOBSTER_API std::optional<char> ReadChar();
		LOBSTER_API std::optional<KeyEvent*> ReadKey();
		LOBSTER_API std::string DumpChars();

		LOBSTER_API bool Autorepeat();
		LOBSTER_API void DisableAutorepeat();
		LOBSTER_API void EnableAutorepeat();

		LOBSTER_API void ClearStates();
		LOBSTER_API void Flush();

		LOBSTER_API void OnKeyEvent(KeyEvent& e);
	}
}