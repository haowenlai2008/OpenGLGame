#include "MyMouse.h"
#include "func.h"

MyMouse::MyMouse() :
	m_State({0, 0, 0, 0, 0, 0, 0.0f}),
	m_FirstMouse(true)
{
}

void MyMouse::processMessage(GLFWwindow* window, double xpos, double ypos)
{
	if (m_FirstMouse)
	{
		m_State.x = xpos;
		m_State.y = ypos;
		m_FirstMouse = false;
	}
	m_State.lastX = m_State.x;
	m_State.lastY = m_State.y;
	m_State.offsetX = m_State.lastX - xpos;
	m_State.offsetY = ypos - m_State.lastY; // reversed since y-coordinates go from bottom to top

	m_State.x = xpos;
	m_State.y = ypos;
}

void MyMouse::processMouseScroll(GLFWwindow* window, double xpos, double ypos)
{
	m_State.scroll = ypos;
}

MyMouse::State MyMouse::getState()
{
	MyMouse::State result = m_State;
	// ÷ÿ÷√∆´“∆÷µ
	m_State.offsetX = 0;
	m_State.offsetY = 0;
	m_State.scroll = 0;
	return result;
}
