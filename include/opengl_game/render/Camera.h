#pragma once
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
};