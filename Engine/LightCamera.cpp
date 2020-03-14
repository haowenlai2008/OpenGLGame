#include "LightCamera.h"
LightCamera::LightCamera()
{
	m_Position = vec3(0.0f, 5.0f, -5.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_Right = vec3(1.0f, 0.0f, 0.0f);
	m_Look = glm::normalize(vec3(0.0f, -1.0f, 1.0f));	// 正面打过来45度光
}


void LightCamera::updateViewProjMatrix()
{
	//计算Look
	vec3 worldUp(0.0f, 1.0f, 0.0f);
	//m_Right = glm::normalize(glm::cross(m_Look, worldUp));
	//m_Up = glm::normalize(glm::cross(m_Right, m_Look));
	//m_View = glm::lookAt(m_Position, m_Position + m_Look, m_Up);

	m_Right = glm::normalize(glm::cross(m_Look, worldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Look));
	m_View = glm::lookAt(m_Position, m_Position + m_Look, m_Up);
	//m_View = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Proj = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 1.0f, 100.0f);
}
