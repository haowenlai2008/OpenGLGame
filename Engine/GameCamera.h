#pragma once
#include "Camera.h"
#include "MyMouse.h"
#include "MyKeyboard.h"
class GameCamera : public Camera
{
public:
	enum class Camera_Type { FirstPerson, ThirdPerson, Free };
	GameCamera();
	GameCamera(const GameCamera&) = delete;
	GameCamera(GameCamera&&) = default;
	GameCamera& operator=(const GameCamera&) = delete;
	GameCamera& operator=(GameCamera&&) = default;
	LL_SYNTHESIZE(vec3, m_Focus, Focus);	// 第三人称相机的target
	LL_SYNTHESIZE(vec3, m_Rotate, Rotate); // 第一人称相机时增加物体的旋转角度
	LL_SYNTHESIZE(float, m_Aspect, Aspect);	//屏幕宽高比
	LL_SYNTHESIZE(float, m_FovY, FovY);		// 视锥夹角
	LL_SYNTHESIZE(float, m_Yaw, Yaw);		// 水平方向旋转角度
	LL_SYNTHESIZE(float, m_Pitch, Pitch);	// 垂直方向旋转角度
	LL_SYNTHESIZE(Camera_Type, m_CType, CameraType);
	void processMouse(MyMouse::State mouseState, MyMouse::State lastMouseState, float dt);
	void processKeyBoard(MyKeyboard::State keyState, float dt);
	virtual void updateViewProjMatrix();
	virtual void resetCamera(Camera_Type type);
protected:
	float m_MouseSensitivity;
	float m_Distance;
};

