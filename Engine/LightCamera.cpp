#include "LightCamera.h"
LightCamera::LightCamera()
{
	m_Position = vec3(0.0f, 10.0f, 10.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_Right = vec3(-1.0f, 0.0f, 0.0f);
	m_Look = glm::normalize(vec3(0.0f, -1.0f, -1.0f));	// 正面打过来45度光
}


void LightCamera::updateViewProjMatrix()
{
	//计算Look
	vec3 worldUp(0.0f, 1.0f, 0.0f);
	m_Right = glm::normalize(glm::cross(m_Look, worldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Look));
	m_View = glm::lookAt(m_Position, m_Position + m_Look, m_Up);
	m_Proj = glm::ortho(0.0f, m_Width, m_Height, 0.0f, -1.0f, 1.0f);
}
