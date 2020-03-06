#pragma once
#include "Camera.h"

// 平行光摄像机，用来实现深度贴图
class LightCamera :	public Camera
{
public:
	LightCamera();
	~LightCamera() = default;
	LightCamera(const LightCamera&) = delete;
	LightCamera& operator=(const LightCamera&) = delete;
	LightCamera(LightCamera&&) = default;
	LightCamera& operator=(LightCamera&&) = default;
	
	LL_SYNTHESIZE(float, m_Width, Width);
	LL_SYNTHESIZE(float, m_Height, Height);
	virtual void updateViewProjMatrix();
};

