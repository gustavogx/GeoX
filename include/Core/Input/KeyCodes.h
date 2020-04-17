#pragma once

namespace GX
{
	typedef enum class KeyCode : u_int16_t
	{
		// This is taken from glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define GX_KEY_SPACE           ::GX::Key::Space
#define GX_KEY_APOSTROPHE      ::GX::Key::Apostrophe    /* ' */
#define GX_KEY_COMMA           ::GX::Key::Comma         /* , */
#define GX_KEY_MINUS           ::GX::Key::Minus         /* - */
#define GX_KEY_PERIOD          ::GX::Key::Period        /* . */
#define GX_KEY_SLASH           ::GX::Key::Slash         /* / */
#define GX_KEY_0               ::GX::Key::D0
#define GX_KEY_1               ::GX::Key::D1
#define GX_KEY_2               ::GX::Key::D2
#define GX_KEY_3               ::GX::Key::D3
#define GX_KEY_4               ::GX::Key::D4
#define GX_KEY_5               ::GX::Key::D5
#define GX_KEY_6               ::GX::Key::D6
#define GX_KEY_7               ::GX::Key::D7
#define GX_KEY_8               ::GX::Key::D8
#define GX_KEY_9               ::GX::Key::D9
#define GX_KEY_SEMICOLON       ::GX::Key::Semicolon     /* ; */
#define GX_KEY_EQUAL           ::GX::Key::Equal         /* = */
#define GX_KEY_A               ::GX::Key::A
#define GX_KEY_B               ::GX::Key::B
#define GX_KEY_C               ::GX::Key::C
#define GX_KEY_D               ::GX::Key::D
#define GX_KEY_E               ::GX::Key::E
#define GX_KEY_F               ::GX::Key::F
#define GX_KEY_G               ::GX::Key::G
#define GX_KEY_H               ::GX::Key::H
#define GX_KEY_I               ::GX::Key::I
#define GX_KEY_J               ::GX::Key::J
#define GX_KEY_K               ::GX::Key::K
#define GX_KEY_L               ::GX::Key::L
#define GX_KEY_M               ::GX::Key::M
#define GX_KEY_N               ::GX::Key::N
#define GX_KEY_O               ::GX::Key::O
#define GX_KEY_P               ::GX::Key::P
#define GX_KEY_Q               ::GX::Key::Q
#define GX_KEY_R               ::GX::Key::R
#define GX_KEY_S               ::GX::Key::S
#define GX_KEY_T               ::GX::Key::T
#define GX_KEY_U               ::GX::Key::U
#define GX_KEY_V               ::GX::Key::V
#define GX_KEY_W               ::GX::Key::W
#define GX_KEY_X               ::GX::Key::X
#define GX_KEY_Y               ::GX::Key::Y
#define GX_KEY_Z               ::GX::Key::Z
#define GX_KEY_LEFT_BRACKET    ::GX::Key::LeftBracket   /* [ */
#define GX_KEY_BACKSLASH       ::GX::Key::Backslash     /* \ */
#define GX_KEY_RIGHT_BRACKET   ::GX::Key::RightBracket  /* ] */
#define GX_KEY_GRAVE_ACCENT    ::GX::Key::GraveAccent   /* ` */
#define GX_KEY_WORLD_1         ::GX::Key::World1        /* non-US #1 */
#define GX_KEY_WORLD_2         ::GX::Key::World2        /* non-US #2 */

/* Function keys */
#define GX_KEY_ESCAPE          ::GX::Key::Escape
#define GX_KEY_ENTER           ::GX::Key::Enter
#define GX_KEY_TAB             ::GX::Key::Tab
#define GX_KEY_BACKSPACE       ::GX::Key::Backspace
#define GX_KEY_INSERT          ::GX::Key::Insert
#define GX_KEY_DELETE          ::GX::Key::Delete
#define GX_KEY_RIGHT           ::GX::Key::Right
#define GX_KEY_LEFT            ::GX::Key::Left
#define GX_KEY_DOWN            ::GX::Key::Down
#define GX_KEY_UP              ::GX::Key::Up
#define GX_KEY_PAGE_UP         ::GX::Key::PageUp
#define GX_KEY_PAGE_DOWN       ::GX::Key::PageDown
#define GX_KEY_HOME            ::GX::Key::Home
#define GX_KEY_END             ::GX::Key::End
#define GX_KEY_CAPS_LOCK       ::GX::Key::CapsLock
#define GX_KEY_SCROLL_LOCK     ::GX::Key::ScrollLock
#define GX_KEY_NUM_LOCK        ::GX::Key::NumLock
#define GX_KEY_PRINT_SCREEN    ::GX::Key::PrintScreen
#define GX_KEY_PAUSE           ::GX::Key::Pause
#define GX_KEY_F1              ::GX::Key::F1
#define GX_KEY_F2              ::GX::Key::F2
#define GX_KEY_F3              ::GX::Key::F3
#define GX_KEY_F4              ::GX::Key::F4
#define GX_KEY_F5              ::GX::Key::F5
#define GX_KEY_F6              ::GX::Key::F6
#define GX_KEY_F7              ::GX::Key::F7
#define GX_KEY_F8              ::GX::Key::F8
#define GX_KEY_F9              ::GX::Key::F9
#define GX_KEY_F10             ::GX::Key::F10
#define GX_KEY_F11             ::GX::Key::F11
#define GX_KEY_F12             ::GX::Key::F12
#define GX_KEY_F13             ::GX::Key::F13
#define GX_KEY_F14             ::GX::Key::F14
#define GX_KEY_F15             ::GX::Key::F15
#define GX_KEY_F16             ::GX::Key::F16
#define GX_KEY_F17             ::GX::Key::F17
#define GX_KEY_F18             ::GX::Key::F18
#define GX_KEY_F19             ::GX::Key::F19
#define GX_KEY_F20             ::GX::Key::F20
#define GX_KEY_F21             ::GX::Key::F21
#define GX_KEY_F22             ::GX::Key::F22
#define GX_KEY_F23             ::GX::Key::F23
#define GX_KEY_F24             ::GX::Key::F24
#define GX_KEY_F25             ::GX::Key::F25

/* Keypad */
#define GX_KEY_KP_0            ::GX::Key::KP0
#define GX_KEY_KP_1            ::GX::Key::KP1
#define GX_KEY_KP_2            ::GX::Key::KP2
#define GX_KEY_KP_3            ::GX::Key::KP3
#define GX_KEY_KP_4            ::GX::Key::KP4
#define GX_KEY_KP_5            ::GX::Key::KP5
#define GX_KEY_KP_6            ::GX::Key::KP6
#define GX_KEY_KP_7            ::GX::Key::KP7
#define GX_KEY_KP_8            ::GX::Key::KP8
#define GX_KEY_KP_9            ::GX::Key::KP9
#define GX_KEY_KP_DECIMAL      ::GX::Key::KPDecimal
#define GX_KEY_KP_DIVIDE       ::GX::Key::KPDivide
#define GX_KEY_KP_MULTIPLY     ::GX::Key::KPMultiply
#define GX_KEY_KP_SUBTRACT     ::GX::Key::KPSubtract
#define GX_KEY_KP_ADD          ::GX::Key::KPAdd
#define GX_KEY_KP_ENTER        ::GX::Key::KPEnter
#define GX_KEY_KP_EQUAL        ::GX::Key::KPEqual

#define GX_KEY_LEFT_SHIFT      ::GX::Key::LeftShift
#define GX_KEY_LEFT_CONTROL    ::GX::Key::LeftControl
#define GX_KEY_LEFT_ALT        ::GX::Key::LeftAlt
#define GX_KEY_LEFT_SUPER      ::GX::Key::LeftSuper
#define GX_KEY_RIGHT_SHIFT     ::GX::Key::RightShift
#define GX_KEY_RIGHT_CONTROL   ::GX::Key::RightControl
#define GX_KEY_RIGHT_ALT       ::GX::Key::RightAlt
#define GX_KEY_RIGHT_SUPER     ::GX::Key::RightSuper
#define GX_KEY_MENU            ::GX::Key::Menu
