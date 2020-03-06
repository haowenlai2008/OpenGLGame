#include "Camera.h"

Camera::Camera():
	m_Position(0.0f, 2.0f, -3.0f),
	m_Look(0.0f, 0.0f, -1.0f),
	m_Right(1.0f, 0.0f, 0.0f),
	m_Up(0.0f, 1.0f, 0.0f)
{
}

void Camera::updateViewProjMatrix()
{
}

mat4 Camera::getViewMat4()
{
	return m_View;
}

mat4 Camera::getProjMat4()
{
	return m_Proj;
}

mat4 Camera::getViewProjMat4()
{
	return m_View * m_Proj;
}

