#pragma once

namespace GX
{
	typedef enum class MouseCode : uint16_t
	{
		// This is from glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define GX_MOUSE_BUTTON_0      ::GX::Mouse::Button0
#define GX_MOUSE_BUTTON_1      ::GX::Mouse::Button1
#define GX_MOUSE_BUTTON_2      ::GX::Mouse::Button2
#define GX_MOUSE_BUTTON_3      ::GX::Mouse::Button3
#define GX_MOUSE_BUTTON_4      ::GX::Mouse::Button4
#define GX_MOUSE_BUTTON_5      ::GX::Mouse::Button5
#define GX_MOUSE_BUTTON_6      ::GX::Mouse::Button6
#define GX_MOUSE_BUTTON_7      ::GX::Mouse::Button7
#define GX_MOUSE_BUTTON_LAST   ::GX::Mouse::ButtonLast
#define GX_MOUSE_BUTTON_LEFT   ::GX::Mouse::ButtonLeft
#define GX_MOUSE_BUTTON_RIGHT  ::GX::Mouse::ButtonRight
#define GX_MOUSE_BUTTON_MIDDLE ::GX::Mouse::ButtonMiddle
