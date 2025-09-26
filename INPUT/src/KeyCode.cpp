// INPUT/src/KeyCode.cpp

#include "KeyCode.hpp"

namespace Lobster
{
	std::unordered_map<unsigned int,KeyCode> keymap;

	void Input::Init()
	{
		keymap['A']              = Key::A;
		keymap['B']              = Key::B;
		keymap['C']              = Key::C;
		keymap['D']              = Key::D;
		keymap['E']              = Key::E;
		keymap['F']              = Key::F;
		keymap['G']              = Key::G;
		keymap['H']              = Key::H;
		keymap['I']              = Key::I;
		keymap['J']              = Key::J;
		keymap['K']              = Key::K;
		keymap['L']              = Key::L;
		keymap['M']              = Key::M;
		keymap['N']              = Key::N;
		keymap['O']              = Key::O;
		keymap['P']              = Key::P;
		keymap['Q']              = Key::Q;
		keymap['R']              = Key::R;
		keymap['S']              = Key::S;
		keymap['T']              = Key::T;
		keymap['U']              = Key::U;
		keymap['V']              = Key::V;
		keymap['W']              = Key::W;
		keymap['X']              = Key::X;
		keymap['Y']              = Key::Y;
		keymap['Z']              = Key::Z;
		
		/* Digit keys */
		keymap['0']              = Key::D0;
		keymap['1']              = Key::D1;
		keymap['2']              = Key::D2;
		keymap['3']              = Key::D3;
		keymap['4']              = Key::D4;
		keymap['5']              = Key::D5;
		keymap['6']              = Key::D6;
		keymap['7']              = Key::D7;
		keymap['8']              = Key::D8;
		keymap['9']              = Key::D9;
		
		/* Function keys */
		keymap[0x70]             = Key::F1;	              /* F1  */
		keymap[0x71]             = Key::F2;	              /* F2  */
		keymap[0x72]             = Key::F3;	              /* F3  */
		keymap[0x73]             = Key::F4;	              /* F4  */
		keymap[0x74]             = Key::F5;	              /* F5  */
		keymap[0x75]             = Key::F6;	              /* F6  */
		keymap[0x76]             = Key::F7;	              /* F7  */
		keymap[0x77]             = Key::F8;	              /* F8  */
		keymap[0x78]             = Key::F9;	              /* F9  */
		keymap[0x79]             = Key::F10;	          /* F10 */
		keymap[0x7A]             = Key::F11;	          /* F11 */
		keymap[0x7B]             = Key::F12;	          /* F12 */
		keymap[0x7C]             = Key::F13;	          /* F13 */
		keymap[0x7D]             = Key::F14;	          /* F14 */
		keymap[0x7E]             = Key::F15;	          /* F15 */
		keymap[0x7F]             = Key::F16;	          /* F16 */
		keymap[0x80]             = Key::F17;	          /* F17 */
		keymap[0x81]             = Key::F18;	          /* F18 */
		keymap[0x82]             = Key::F19;	          /* F19 */
		keymap[0x83]             = Key::F20;	          /* F20 */
		keymap[0x84]             = Key::F21;	          /* F21 */
		keymap[0x85]             = Key::F22;	          /* F22 */
		keymap[0x86]             = Key::F23;	          /* F23 */
		keymap[0x87]             = Key::F24;	          /* F24 */
		
		/* Special keys */
		keymap[0x1B]             = Key::Escape;
		keymap[0x0D]             = Key::Enter;
		keymap[0x09]             = Key::Tab;
		keymap[0x08]             = Key::Backspace;
		keymap[0x2D]             = Key::Insert;
		keymap[0x2E]             = Key::Delete;
		keymap[0x27]             = Key::Right;
		keymap[0x25]             = Key::Left;
		keymap[0x28]             = Key::Down;
		keymap[0x26]             = Key::Up;
		keymap[0x21]             = Key::PageUp;           /* Page Up */
		keymap[0x22]             = Key::PageDown;         /* Page Down */
		keymap[0x24]             = Key::Home;
		keymap[0x23]             = Key::End;
		keymap[0x14]             = Key::CapsLock;
		keymap[0x91]             = Key::ScrollLock;
		keymap[0x90]             = Key::NumLock;
		keymap[0x2C]             = Key::PrintScreen;
		keymap[0x13]             = Key::Pause;
		
		/* Modifier keys */
		keymap[0x10]             = Key::LeftShift;
		keymap[0x11]             = Key::LeftControl;
		keymap[0x12]             = Key::LeftAlt;          /* Alt key */
		keymap[0x5B]             = Key::LeftSuper;        /* Windows key */
		keymap[0x5C]             = Key::RightSuper;
		
		/* Numpad keys */
		keymap[0x60]             = Key::KP0;			  /* 0 */
		keymap[0x61]             = Key::KP1;			  /* 1 */
		keymap[0x62]             = Key::KP2;			  /* 2 */
		keymap[0x63]             = Key::KP3;			  /* 3 */
		keymap[0x64]             = Key::KP4;			  /* 4 */
		keymap[0x65]             = Key::KP5;			  /* 5 */
		keymap[0x66]             = Key::KP6;			  /* 6 */
		keymap[0x67]             = Key::KP7;			  /* 7 */
		keymap[0x68]             = Key::KP8;			  /* 8 */
		keymap[0x69]             = Key::KP9;			  /* 9 */
		keymap[0x6E]             = Key::KPDecimal;        /* . */
		keymap[0x6F]             = Key::KPDivide;	      /* / */
		keymap[0x6A]             = Key::KPMultiply;	      /* * */
		keymap[0x6D]             = Key::KPSubtract;	      /* - */
		keymap[0x6B]             = Key::KPAdd;		      /* + */
													      
		/* Other keys */							      
		keymap[0x20]             = Key::Space;            /*   */
		keymap[0xDE]             = Key::Apostrophe;       /* ' */
		keymap[0xBC]             = Key::Comma;            /* , */
		keymap[0xBD]             = Key::Minus;            /* - */
		keymap[0xBE]             = Key::Period;           /* . */
		keymap[0xBF]             = Key::Slash;            /* / */
		keymap[0xBA]             = Key::Semicolon;        /* ; */
		keymap[0xBB]             = Key::Equal;            /* = */
		keymap[0xDB]             = Key::LeftBracket;      /* [ */
		keymap[0xDC]             = Key::Backslash;        /* \ */
		keymap[0xDD]             = Key::RightBracket;     /* ] */
		keymap[0xC0]             = Key::GraveAccent;      /* ` */
	}

	KeyCode Input::Win32ToGlfwKey(unsigned int win32key)
	{
		return keymap[win32key];
	}
}