#include "MyKeyboard.h"
#include <map>
#include "func.h"
MyKeyboard::State __cdecl MyKeyboard::getState()
{
	return m_State;
}


// 遍历键盘枚举的索引
using Keys = MyKeyboard::Keys;
static vector<int> keyCodeIndex = {
	Keys::KEY_SPACE,
	Keys::KEY_APOSTROPHE,
	Keys::KEY_COMMA,
	Keys::KEY_MINUS,
	Keys::KEY_PERIOD,
	Keys::KEY_SLASH,
	Keys::KEY_0,
	Keys::KEY_1,
	Keys::KEY_2,
	Keys::KEY_3,
	Keys::KEY_4,
	Keys::KEY_5,
	Keys::KEY_6,
	Keys::KEY_7,
	Keys::KEY_8,
	Keys::KEY_9,
	Keys::KEY_SEMICOLON,
	Keys::KEY_EQUAL,
	Keys::KEY_A,
	Keys::KEY_B,
	Keys::KEY_C,
	Keys::KEY_D,
	Keys::KEY_E,
	Keys::KEY_F,
	Keys::KEY_G,
	Keys::KEY_H,
	Keys::KEY_I,
	Keys::KEY_J,
	Keys::KEY_K,
	Keys::KEY_L,
	Keys::KEY_M,
	Keys::KEY_N,
	Keys::KEY_O,
	Keys::KEY_P,
	Keys::KEY_Q,
	Keys::KEY_R,
	Keys::KEY_S,
	Keys::KEY_T,
	Keys::KEY_U,
	Keys::KEY_V,
	Keys::KEY_W,
	Keys::KEY_X,
	Keys::KEY_Y,
	Keys::KEY_Z,
	Keys::KEY_LEFT_BRACKET,
	Keys::KEY_BACKSLASH,
	Keys::KEY_RIGHT_BRACKET,
	Keys::KEY_GRAVE_ACCENT,
	Keys::KEY_WORLD_1,
	Keys::KEY_WORLD_2,
	Keys::KEY_ESCAPE,
	Keys::KEY_ENTER,
	Keys::KEY_TAB,
	Keys::KEY_BACKSPACE,
	Keys::KEY_INSERT,
	Keys::KEY_DELETE,
	Keys::KEY_RIGHT,
	Keys::KEY_LEFT,
	Keys::KEY_DOWN,
	Keys::KEY_UP,
	Keys::KEY_PAGE_UP,
	Keys::KEY_PAGE_DOWN,
	Keys::KEY_HOME,
	Keys::KEY_END,
	Keys::KEY_CAPS_LOCK,
	Keys::KEY_SCROLL_LOCK,
	Keys::KEY_NUM_LOCK,
	Keys::KEY_PRINT_SCREEN,
	Keys::KEY_PAUSE,
	Keys::KEY_F1,
	Keys::KEY_F2,
	Keys::KEY_F3,
	Keys::KEY_F4,
	Keys::KEY_F5,
	Keys::KEY_F6,
	Keys::KEY_F7,
	Keys::KEY_F8,
	Keys::KEY_F9,
	Keys::KEY_F10,
	Keys::KEY_F11,
	Keys::KEY_F12,
	Keys::KEY_F13,
	Keys::KEY_F14,
	Keys::KEY_F15,
	Keys::KEY_F16,
	Keys::KEY_F17,
	Keys::KEY_F18,
	Keys::KEY_F19,
	Keys::KEY_F20,
	Keys::KEY_F21,
	Keys::KEY_F22,
	Keys::KEY_F23,
	Keys::KEY_F24,
	Keys::KEY_F25,
	Keys::KEY_KP_0,
	Keys::KEY_KP_1,
	Keys::KEY_KP_2,
	Keys::KEY_KP_3,
	Keys::KEY_KP_4,
	Keys::KEY_KP_5,
	Keys::KEY_KP_6,
	Keys::KEY_KP_7,
	Keys::KEY_KP_8,
	Keys::KEY_KP_9,
	Keys::KEY_KP_DECIMAL,
	Keys::KEY_KP_DIVIDE,
	Keys::KEY_KP_MULTIPLY,
	Keys::KEY_KP_SUBTRACT,
	Keys::KEY_KP_ADD,
	Keys::KEY_KP_ENTER,
	Keys::KEY_KP_EQUAL,
	Keys::KEY_LEFT_SHIFT,
	Keys::KEY_LEFT_CONTROL,
	Keys::KEY_LEFT_ALT,
	Keys::KEY_LEFT_SUPER,
	Keys::KEY_RIGHT_SHIFT,
	Keys::KEY_RIGHT_CONTROL,
	Keys::KEY_RIGHT_ALT,
	Keys::KEY_RIGHT_SUPER,
	Keys::KEY_MENU
};
void MyKeyboard::processInput(GLFWwindow* window)
{
	for (auto index : keyCodeIndex)
	{
		int keyState = glfwGetKey(window, index);
		if (keyState == GLFW_PRESS)
		{
			keyDown(index);
		}
		else if (keyState == GLFW_RELEASE)
		{
			keyUp(index);
		}
	}
}
void MyKeyboard::haha(GLFWwindow* window)
{
	std::cout << "diu" << std::endl;
}
MyKeyboard::MyKeyboard() noexcept(false)
{
}
MyKeyboard::~MyKeyboard()
{
}

