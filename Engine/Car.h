#pragma once
#include "Node.h"
class Wheel;
class Car :
	public Node
{
public:
	enum class DriveState
	{
		Left,		//向左
		Right,		//向右
		Straight	//直走
	};
	CREATE_FUNC(Car);
	virtual bool init() override;
	virtual void update(float dt) override;
	void speedUpdate(float dt);	// 速度更新
	vec3 getCenter(); // 获得中心点的世界坐标
	vec3 getHeadPos();	// 获得车头的位置
	Wheel* m_pLeftWheel; // 左轮子
	Wheel* m_pRightWheel; // 右轮子
	Wheel* m_WheelLists[4]; // 所有车轮
	vec3 m_Center;// 车的中心
	vec3 m_Head;// 车的中心
	float m_Speed;	// 车速
	float m_mSpeed;	// 最大车速
	float m_fSpeed;	// 前进加速度
	float m_aSpeed;	// 当前加速度
	float m_bSpeed;	// 刹车加速度
	float m_nSpeed;	// 不动时的加速度（滑动摩擦产生的减速）
	float m_Length;	// 车长
	float m_innerAngle;	// 车转弯时靠旋转圆心的车轮的偏移的角度
	float m_innerRadians;// 车转弯时靠旋转圆心的车轮的偏移的弧度
	float m_outerAngle;	// 车转弯时不靠旋转圆心的车轮的偏移的角度
	float m_outerRadians;// 车转弯时不靠旋转圆心的车轮的偏移的弧度
	float m_C;			//车子转弯时圆的周长
	float m_turnAngle;	// 转弯时每秒车身旋转的角度
	bool m_BrakeMark;	// 刹车标记
	DriveState m_DState;
};

