#include "Car.h"
#include "Cube.h"
#include "Wheel.h"
#include "LeftWheel.h"
#include "RightWheel.h"
#include "BaseManager.h"
#include "GameCamera.h"
#include "MyKeyboard.h"
#include <sstream>
bool Car::init()
{
	m_Speed = 0.0f;
	m_DState = DriveState::Straight;

	m_mSpeed = 10.0f;	// 最大速度
	m_fSpeed = 5.0f;	// 前进加速度
	m_aSpeed = 0.0f;	// 当前加速度
	m_bSpeed = 7.0f;	// 刹车加速度
	m_nSpeed = 3.0f;	// 不操作时车子的减速度
	m_BrakeMark = false;	//刹车标记

	//Node::Material material = {
	//	{0.2f, 0.2f, 0.2f, 1.0f},
	//	{0.3f, 0.3f, 0.3f, 1.0f},
	//	{0.3f, 0.3f, 0.3f, 10.0f},
	//	{1.0f, 1.0f, 1.0f, 1.0f}
	//};
	for (int i = 0; i < 4; i++)
	{
		if (i % 2 == 1)
			m_WheelLists[i] = RightWheel::create();
		else
			m_WheelLists[i] = LeftWheel::create();
		this->addChild(m_WheelLists[i]);
	}
	float v = 0.5f; // 车轮所在水平线
	m_pLeftWheel = m_WheelLists[0];	// 左前轮
	m_pRightWheel = m_WheelLists[1];	// 右前轮
	m_WheelLists[0]->setLocalPosition(vec3(-0.5f, v, 0.0f)); // 左前轮
	m_WheelLists[1]->setLocalPosition(vec3(0.5f, v, 0.0f));	 // 右前轮
	m_WheelLists[2]->setLocalPosition(vec3(-0.5f, v, 2.5f)); // 左2
	m_WheelLists[3]->setLocalPosition(vec3(0.5f, v, 2.5f)); // 右2

	float wheelRadius = m_pLeftWheel->getRadius();
	// 车头
	Cube* head = Cube::create(Entity_Type::WithTex);
	head->setTexture("carhead.jpg");
	head->setLocalPosition(vec3(0.0f, 1 + v + wheelRadius, 0.0f));
	head->setScale(vec3(2.0f, 2.0f, 1.0f));
	this->addChild(head);
	
	// 车后面的板子
	Cube* board = Cube::create(Entity_Type::WithTex);
	board->setTexture("surface.jpg");
	board->setScale(vec3(2.0f, 0.5f, 2.75f));
	board->setLocalPosition(vec3(0.0f, 0.25 + v + wheelRadius, 1.875f));
	this->addChild(board);
	
	//setMaterial(std::move(material));
	//前后轮距离
	m_Length = head->getLocalPosition().z - board->getLocalPosition().z;
	//平移一下所有物体，把重心设置成后轮轴的中心
	for (auto& ref : childs)
	{
		auto pos = ref->getLocalPosition();
		ref->setPosition(vec3(pos.x, pos.y, pos.z + m_Length));
	}
	m_Center = vec3(0.0f, board->getLocalPosition().y, m_Length / 2.0f);// 设置一下中心
	m_Head = head->getLocalPosition();	// 设置车头位置

	// 计算转弯时的参数
	m_innerAngle = 20.0f;
	m_innerRadians =  glm::radians(m_innerAngle);	// 前轮转弯时的角度
	float r1 = m_Length / tanf(m_innerRadians); //转弯时圆的半径(靠圆心的后车轮离圆心的距离
	float disRL = m_pRightWheel->getLocalPosition().x - m_pLeftWheel->getLocalPosition().x; //左右车轮的间距
	float r2 = r1 + disRL; // 不靠圆心的后车轮离圆心的距离
	m_outerRadians = atanf(m_Length / r2);
	m_outerAngle = m_outerRadians * (180.0f / glm::pi<float>());
	float r = r1 + disRL / 2.0f;	// 车实际旋转的时候的半径
	m_C = glm::two_pi<float>() * r;	//旋转时的周长
	return true;
}

void Car::update(float dt)
{
	if (BaseManager::getInstance()->getCamera()->getCameraType() == GameCamera::Camera_Type::Free)
		return;
	float CWheel = 0.75 * 2 * glm::pi<float>();// 车轮周长
	
	MyKeyboard::State keyState = BaseManager::getInstance()->getKeyboardState();
	auto originRotateL = m_pLeftWheel->getRotate();
	auto originRotateR = m_pRightWheel->getRotate();
	speedUpdate(dt);	//更新小车速度
	
	// 前轮方向
	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_A))
	{
		m_pLeftWheel->setRotate(vec3(originRotateL.x, m_innerAngle, originRotateL.z));
		m_pRightWheel->setRotate(vec3(originRotateR.x, m_outerAngle, originRotateR.z));
		m_DState = DriveState::Left;
	}
	else if (keyState.isKeyDown(MyKeyboard::Keys::KEY_D))
	{
		m_pLeftWheel->setRotate(vec3(originRotateL.x, -m_outerAngle, originRotateL.z));
		m_pRightWheel->setRotate(vec3(originRotateR.x, -m_innerAngle, originRotateR.z));
		m_DState = DriveState::Right;
	}
	else
	{
		m_pLeftWheel->setRotate(vec3(originRotateL.x, 0.0f, originRotateL.z));
		m_pRightWheel->setRotate(vec3(originRotateR.x, 0.0f, originRotateR.z));
		m_DState = DriveState::Straight;
	}



	// 移动的时候各车轮的旋转以及车身的旋转和车身的位移
	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_W))
	{
		m_aSpeed = m_fSpeed;	//更新加速度为前进加速度
	}
	else if (keyState.isKeyDown(MyKeyboard::Keys::KEY_S))
	{
		m_aSpeed = -m_fSpeed;	//更新加速度为前进加速度的反方向
	}
	else
	{
		m_aSpeed = m_Speed + 0.05f < 0.1f ?  m_nSpeed : -m_nSpeed; // 不前不后改成滑动摩擦加速度
	}

	// 转弯逻辑实现
	if (m_DState != DriveState::Straight)
	{
		// 车身旋转
		if (abs(m_Speed) > 1.0f) 
		{
			float tmpAngle = (m_Speed / m_C) * 360.0f * dt;
			if (m_DState == DriveState::Left)
			{
				Rotate(vec3(0.0f, -tmpAngle, 0.0f));
			}
			else if (m_DState == DriveState::Right)
			{
				Rotate(vec3(0.0f, tmpAngle, 0.0f));
			}
		}

	}
	//车身移动，做个约束，避免车速接近0时做小动作
	if (abs(m_Speed) > 1.0f)
	{
		
		vec3 originPos = getPosition();
		vec3 speed = m_Speed * getLookVector();
		setPosition(originPos + speed * dt);
	}


	// 刹车
	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_SPACE))
	{
		m_aSpeed = m_Speed < 0.0f ? m_bSpeed : -m_bSpeed; // 更新加速度为刹车加速度
		m_BrakeMark = true;
	}
	else
	{
		m_BrakeMark = false;
	}

	float angel = m_Speed / CWheel * 360.0f * dt;// 一个update车轮垂直方向转过的角度
	//车轮旋转
	if (abs(m_Speed) > 1.0f)
	{
		for (auto& wheel : m_WheelLists)
		{
			wheel->Rotate(vec3(-angel, 0.0f, 0.0f));
		}
	}

}

// 速度更新
void Car::speedUpdate(float dt)
{
	m_Speed += m_aSpeed * dt; // 加速度
	// 限速
	if (m_Speed < -m_mSpeed)
	{
		m_Speed = -m_mSpeed;
	}
	if (m_Speed > m_mSpeed)
	{
		m_Speed = m_mSpeed;
	}
}

// 获得中心点的世界坐标
vec3 Car::getCenter()
{
	vec3 result = vec3(getModelMatrix() * glm::vec4(m_Center, 1.0f));
	//XMVECTOR v = XMLoadFloat3(&m_Center);
	//v = XMVector3Transform(v, getModelMatrix());
	//XMStoreFloat3(&result, v);
	return result;
}

// 获得车头的位置
vec3 Car::getHeadPos()
{
	vec3 result = vec3(getModelMatrix() * glm::vec4(m_Head, 1.0f));
	return result;
}
