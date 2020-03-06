#include "GameCamera.h"

GameCamera::GameCamera() :
	m_Focus(0.0f, 0.0f, 0.0f),
	m_Rotate(0.0f, 0.0f, 0.0f),
	m_Yaw(90.0f),
	m_Pitch(0.0f),
	m_Aspect(1.0f),
	m_FovY(90.0f),
	m_Distance(5.0f),
	m_CType(Camera_Type::Free),
	m_MouseSensitivity(0.5f)
{

}



void GameCamera::processMouse(MyMouse::State mouseState, MyMouse::State lastMouseState, float dt)
{
	float xoffset = -m_MouseSensitivity * (mouseState.offsetX);
	float yoffset = -m_MouseSensitivity * (mouseState.offsetY);
	float scrollWheelValue = mouseState.scroll;

	if (m_CType == Camera_Type::Free || m_CType == Camera_Type::FirstPerson)
	{
		m_Yaw += xoffset;
		m_Pitch += yoffset;
		m_FovY -= scrollWheelValue * 0.1f;
		//std::wostringstream outs;
		//outs.precision(6);
		//outs << L"   "
		//	<< L"m_Yaw: " << m_Yaw
		//	<< L"m_Pitch: " << m_Pitch
		//	<< L"look: " << m_Look.x << "," << m_Look.y << "," << m_Look.z;
		//SetWindowText(BaseManager::getInstance()->getMainWindow(), outs.str().c_str());
		//std::wostringstream outs;
		//outs.precision(6);
		//outs << L"   "
		//	<< L"x: " << mouseState.x
		//	<< L"y: " << mouseState.y
		//	<< L" x2: " << mouseState.realX
		//	<< L" y2: " << mouseState.realY;
		//SetWindowText(BaseManager::getInstance()->getMainWindow(), outs.str().c_str());
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
		if (m_FovY > 134.0f)
			m_FovY = 134.0f;
		if (m_FovY < 46.0f)
			m_FovY = 46.0f;
	}
	else if (m_CType == Camera_Type::ThirdPerson)
	{
		m_Yaw += xoffset;
		m_Pitch -= yoffset;
		m_Distance -= scrollWheelValue * 0.1f;
		//std::wostringstream outs;
		//outs.precision(6);
		//outs << L"   "
		//	<< L"m_Yaw: " << m_Yaw
		//	<< L" yoffset: " << yoffset
		//	<< L" m_Pitch: " << m_Pitch
		//	<< L" look: " << m_Look.x << "," << m_Look.y << "," << m_Look.z;
		//SetWindowText(BaseManager::getInstance()->getMainWindow(), outs.str().c_str());
		//std::wostringstream outs;
		//outs.precision(6);
		//outs << L"   "
		//	<< L"x: " << m_Position.x
		//	<< L"y: " << m_Position.y
		//	<< L" x2: " << mouseState.realX
		//	<< L" y2: " << mouseState.realY
		//	<< L" x3: " << xoffset
		//	<< L" y3: " << yoffset;
		//SetWindowText(BaseManager::getInstance()->getMainWindow(), outs.str().c_str());

		//限制垂直方向的角度
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		//限制缩放距离
		if (m_Distance < 1.0f)
			m_Distance = 1.0f;
		if (m_Distance > 10.0f)
			m_Distance = 10.0f;
	}
}

void GameCamera::processKeyBoard(MyKeyboard::State keyState, float dt)
{
	if (m_CType == Camera_Type::Free)
	{
		vec3 pos = m_Position;
		if (keyState.isKeyDown(MyKeyboard::Keys::KEY_A))
			pos -= m_Right * dt * 3.0f;
		if (keyState.isKeyDown(MyKeyboard::Keys::KEY_D))
			pos += m_Right * dt * 3.0f;
		if (keyState.isKeyDown(MyKeyboard::Keys::KEY_S))
			pos -= m_Look * dt * 3.0f;
		if (keyState.isKeyDown(MyKeyboard::Keys::KEY_W))
			pos += m_Look * dt * 3.0f;
		m_Position = pos;
		//updateViewMatrix();
	}
}

void GameCamera::updateViewProjMatrix()
{
	glm::vec3 front;

	//计算面向相机前方的向量
	float Yaw = m_Yaw, Pitch = m_Pitch;
	//第一人称相机要加上物体自身的旋转量
	if (m_CType == Camera_Type::FirstPerson)
	{
		Yaw -= m_Rotate.y;
		Pitch -= m_Rotate.x;
	}

	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	vec3 look = glm::normalize(front);
	//计算Look
	if (m_CType == Camera_Type::Free || m_CType == Camera_Type::FirstPerson)
	{
		m_Look = look;
	}
	else if (m_CType == Camera_Type::ThirdPerson)	// 利用look反向求一个look
	{
		m_Look = -look;
		m_Position = m_Focus + look * m_Distance;
	}
	vec3 worldUp(0.0f, 1.0f, 0.0f);
	m_Right = glm::normalize(glm::cross(m_Look, worldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Look));
	m_View = glm::lookAt(m_Position, m_Position + m_Look, m_Up);
	m_Proj = glm::perspective(glm::radians(m_FovY), m_Aspect, 0.1f, 100.0f);
}

void GameCamera::resetCamera(Camera_Type type)
{
	m_MouseSensitivity = 0.5f;
	m_Position = vec3(0.0f, 2.0f, -3.0f);
	m_Look = vec3(0.0f, 0.0f, -1.0f);
	m_Right = vec3(-1.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_Focus = vec3(0.0f, 0.0f, 0.0f);
	m_Yaw = type == Camera_Type::ThirdPerson ? 90.0f : -90.0f;
	m_Pitch = type == Camera_Type::ThirdPerson ? 45.0f : 0.0f;
	//m_Aspect = 1.0f;
	m_FovY = 90.0f;
	m_Distance = 5.0f;
}


