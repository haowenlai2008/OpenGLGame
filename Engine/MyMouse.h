#pragma once
#include "func.h"
class GLFWwindow;
class MyMouse
{
public:
	struct State
	{
		int x;
		int y;
		int offsetX;
		int offsetY;
		int lastX;
		int lastY;
		float scroll;
	};
	MyMouse();
	void processMessage(GLFWwindow* window, double xpos, double ypos);
	void processMouseScroll(GLFWwindow* window, double xpos, double ypos);
	MyMouse& operator=(const MyMouse&) = delete;
	MyMouse& operator=(MyMouse&&) = default;
	MyMouse(const MyMouse&) = delete;
	MyMouse(MyMouse&&) = default;
	State getState();
private:
	State m_State;
	bool m_FirstMouse;
};

