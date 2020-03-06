#pragma once
//#include <glad.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <iostream>
#include <vector>
#include "func.h"

class Camera
{
public:

	Camera();
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = default;
	Camera& operator=(Camera&&) = default;
	LL_SYNTHESIZE(vec3, m_Position, Position);
	LL_SYNTHESIZE(vec3, m_Right, Right);
	LL_SYNTHESIZE(vec3, m_Up, Up);
	LL_SYNTHESIZE(vec3, m_Look, Look);


	virtual void updateViewProjMatrix();

	virtual mat4 getViewMat4();
	virtual mat4 getProjMat4();
	virtual mat4 getViewProjMat4();
protected:
	mat4 m_View;
	mat4 m_Proj;
//public:
	//// Camera Attributes
	//glm::vec3 Position;
	//glm::vec3 Front;
	//glm::vec3 Up;
	//glm::vec3 Right;
	//glm::vec3 WorldUp;
	//// Euler Angles
	//float Yaw;
	//float Pitch;
	//// Camera options
	//float MovementSpeed;
	//float MouseSensitivity;
	//float Zoom;

	//bool isFree;
	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
//	glm::mat4 GetViewMatrix()
//	{
//		return glm::lookAt(Position, Position + Front, Up);
//	}
//
//	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
//	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
//	{
//		float velocity = MovementSpeed * deltaTime;
//		glm::vec3 front = isFree ? Front : glm::vec3(Front.x, 0, Front.z);//是否自由移动
//		if (direction == FORWARD)
//			Position += glm::vec3(front.x, front.y, front.z) * velocity;
//		if (direction == BACKWARD)
//			Position -= glm::vec3(front.x, front.y, front.z) * velocity;
//		if (direction == LEFT)
//			Position -= Right * velocity;
//		if (direction == RIGHT)
//			Position += Right * velocity;
//	}
//
//	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
//	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//	{
//		xoffset *= MouseSensitivity;
//		yoffset *= MouseSensitivity;
//
//		Yaw += xoffset;
//		Pitch += yoffset;
//
//		// Make sure that when pitch is out of bounds, screen doesn't get flipped
//		if (constrainPitch)
//		{
//			if (Pitch > 89.0f)
//				Pitch = 89.0f;
//			if (Pitch < -89.0f)
//				Pitch = -89.0f;
//		}
//
//		// Update Front, Right and Up Vectors using the updated Euler angles
//		updateCameraVectors();
//	}
//
//	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
//	void ProcessMouseScroll(float yoffset)
//	{
//		if (Zoom >= 1.0f && Zoom <= 45.0f)
//			Zoom -= yoffset;
//		if (Zoom <= 1.0f)
//			Zoom = 1.0f;
//		if (Zoom >= 45.0f)
//			Zoom = 45.0f;
//	}
//
//private:
//	// Calculates the front vector from the Camera's (updated) Euler Angles
//	void updateCameraVectors()
//	{
//		// Calculate the new Front vector
//		glm::vec3 front;
//		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//		front.y = sin(glm::radians(Pitch));
//		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//		Front = glm::normalize(front);
//		// Also re-calculate the Right and Up vector
//		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//		Up = glm::normalize(glm::cross(Right, Front));
//	}
};