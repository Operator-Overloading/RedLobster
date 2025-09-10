// INPUT/src/KeyCode.cpp

#include "KeyCode.hpp"

namespace Lobster
{
	KeyCode Win32ToGlfwKey(int win32Key)
	{
		switch (win32Key)
		{
		// Alphabet keys
		case 'A':              return Key::A;
		case 'B':              return Key::B;
		case 'C':              return Key::C;
		case 'D':              return Key::D;
		case 'E':              return Key::E;
		case 'F':              return Key::F;
		case 'G':              return Key::G;
		case 'H':              return Key::H;
		case 'I':              return Key::I;
		case 'J':              return Key::J;
		case 'K':              return Key::K;
		case 'L':              return Key::L;
		case 'M':              return Key::M;
		case 'N':              return Key::N;
		case 'O':              return Key::O;
		case 'P':              return Key::P;
		case 'Q':              return Key::Q;
		case 'R':              return Key::R;
		case 'S':              return Key::S;
		case 'T':              return Key::T;
		case 'U':              return Key::U;
		case 'V':              return Key::V;
		case 'W':              return Key::W;
		case 'X':              return Key::X;
		case 'Y':              return Key::Y;
		case 'Z':              return Key::Z;
		
		/* Digit keys */
		case '0':              return Key::D0;
		case '1':              return Key::D1;
		case '2':              return Key::D2;
		case '3':              return Key::D3;
		case '4':              return Key::D4;
		case '5':              return Key::D5;
		case '6':              return Key::D6;
		case '7':              return Key::D7;
		case '8':              return Key::D8;
		case '9':              return Key::D9;
		
		/* Function keys */
		case 0x70:             return Key::F1;	 /* F1  */
		case 0x71:             return Key::F2;	 /* F2  */
		case 0x72:             return Key::F3;	 /* F3  */
		case 0x73:             return Key::F4;	 /* F4  */
		case 0x74:             return Key::F5;	 /* F5  */
		case 0x75:             return Key::F6;	 /* F6  */
		case 0x76:             return Key::F7;	 /* F7  */
		case 0x77:             return Key::F8;	 /* F8  */
		case 0x78:             return Key::F9;	 /* F9  */
		case 0x79:             return Key::F10;	 /* F10 */
		case 0x7A:             return Key::F11;	 /* F11 */
		case 0x7B:             return Key::F12;	 /* F12 */
		case 0x7C:             return Key::F13;	 /* F13 */
		case 0x7D:             return Key::F14;	 /* F14 */
		case 0x7E:             return Key::F15;	 /* F15 */
		case 0x7F:             return Key::F16;	 /* F16 */
		case 0x80:             return Key::F17;	 /* F17 */
		case 0x81:             return Key::F18;	 /* F18 */
		case 0x82:             return Key::F19;	 /* F19 */
		case 0x83:             return Key::F20;	 /* F20 */
		case 0x84:             return Key::F21;	 /* F21 */
		case 0x85:             return Key::F22;	 /* F22 */
		case 0x86:             return Key::F23;	 /* F23 */
		case 0x87:             return Key::F24;	 /* F24 */
		
		/* Special keys */
		case 0x1B:             return Key::Escape;
		case 0x0D:             return Key::Enter;
		case 0x09:             return Key::Tab;
		case 0x08:             return Key::Backspace;
		case 0x2D:             return Key::Insert;
		case 0x2E:             return Key::Delete;
		case 0x27:             return Key::Right;
		case 0x25:             return Key::Left;
		case 0x28:             return Key::Down;
		case 0x26:             return Key::Up;
		case 0x21:             return Key::PageUp;        /* Page Up */
		case 0x22:             return Key::PageDown;      /* Page Down */
		case 0x24:             return Key::Home;
		case 0x23:             return Key::End;
		case 0x14:             return Key::CapsLock;
		case 0x91:             return Key::ScrollLock;
		case 0x90:             return Key::NumLock;
		case 0x2C:             return Key::PrintScreen;
		case 0x13:             return Key::Pause;
		
		/* Modifier keys */
		case 0x10:             return Key::LeftShift;
		case 0x11:             return Key::LeftControl;
		case 0x12:             return Key::LeftAlt;       /* Alt key */
		case 0x5B:             return Key::LeftSuper;     /* Windows key */
		case 0x5C:             return Key::RightSuper;
		
		/* Numpad keys */
		case 0x60:             return Key::KP0;			  /* 0 */
		case 0x61:             return Key::KP1;			  /* 1 */
		case 0x62:             return Key::KP2;			  /* 2 */
		case 0x63:             return Key::KP3;			  /* 3 */
		case 0x64:             return Key::KP4;			  /* 4 */
		case 0x65:             return Key::KP5;			  /* 5 */
		case 0x66:             return Key::KP6;			  /* 6 */
		case 0x67:             return Key::KP7;			  /* 7 */
		case 0x68:             return Key::KP8;			  /* 8 */
		case 0x69:             return Key::KP9;			  /* 9 */
		case 0x6E:             return Key::KPDecimal;     /* . */
		case 0x6F:             return Key::KPDivide;	  /* / */
		case 0x6A:             return Key::KPMultiply;	  /* * */
		case 0x6D:             return Key::KPSubtract;	  /* - */
		case 0x6B:             return Key::KPAdd;		  /* + */
		
		/* Other keys */
		case 0x20:             return Key::Space;         /*   */
		case 0xDE:             return Key::Apostrophe;    /* ' */
		case 0xBC:             return Key::Comma;         /* , */
		case 0xBD:             return Key::Minus;         /* - */
		case 0xBE:             return Key::Period;        /* . */
		case 0xBF:             return Key::Slash;         /* / */
		case 0xBA:             return Key::Semicolon;     /* ; */
		case 0xBB:             return Key::Equal;         /* = */
		case 0xDB:             return Key::LeftBracket;   /* [ */
		case 0xDC:             return Key::Backslash;     /* \ */
		case 0xDD:             return Key::RightBracket;  /* ] */
		case 0xC0:             return Key::GraveAccent;   /* ` */
		
		default: return 0;
		}
	}
}