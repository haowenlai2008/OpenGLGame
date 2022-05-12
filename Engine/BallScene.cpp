#include "BallScene.h"
#include "SkyBox.h"
#include "BaseManager.h"
#include "GameCamera.h"
#include "LightCamera.h"
#include "Ground.h"
#include "Sphere.h"
#include "Cube.h"
#include "bulletHead.h"
#include "Circle.h"
#include "CylinderNoCap.h"
#include "Cylinder.h"
#include "const.h"
bool BallScene::init()
{
	SkyBox* skyBox = SkyBox::create();
	this->addChild(skyBox);



	Ground* gnd = Ground::create(MaterialType::PBR);
	//gnd->setColor(Const::EntityColor::Grey);
	this->addChild(gnd);


	//auto cb = Sphere::create(MaterialType::WithColorAndLight);
	////cb->Rotate(vec3(0.0f, 0.0f, 90.0f));
	////cb->setScale(vec3(1.0f, 2.0f, 1.0f));
	//cb->setPosition(vec3(1.5f, 0.0f, 0.0f));
	//cb->setMaterial(vec3(0.5f, 0.5f, 0.5f), 32.0f);
	//cb->setColor(Const::EntityColor::Pink);
	//this->addChild(cb);

	auto cb2 = Sphere::create(MaterialType::WithColorAndLight);
	//cb->Rotate(vec3(0.0f, 0.0f, 90.0f));
	//cb->setScale(vec3(1.0f, 2.0f, 1.0f));
	cb2->addSphereRigidBody();
	cb2->setPosition(vec3(-1.5f, 0.0f, 0.0f));
	cb2->setMaterial(vec3(0.1f, 0.1f, 0.1f), 32.0f);
	cb2->setColor(Const::EntityColor::Pink);

	this->addChild(cb2);

	m_focus = Sphere::create(MaterialType::PBR);
	//dynamic_cast<Sphere*>(m_focus)->setTexture("white.png");
	dynamic_cast<Sphere*>(m_focus)->setColor(Const::EntityColor::Yellow);
	m_focus->addSphereRigidBody();
	m_focus->setPosition(vec3(1.5f,2.0f, 0.0f));
	this->addChild(m_focus);


	//auto sp = Sphere::create(MaterialType::WithColorAndLight);
	//sp->setPosition(vec3(0.0f, 2.0f, -4.0f));
	//sp->setColor(Const::EntityColor::Yellow);
	//sp->setRotate(vec3(0.0f, 45.0f, 0.0f));
	//this->addChild(sp);
	return true;
}

void BallScene::update(float dt)
{
	auto camera = BaseManager::getInstance()->getCamera();
	// 切换摄像机的逻辑
	auto pBM = BaseManager::getInstance();
	auto keyState = pBM->getKeyboardState();
	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_1) && camera->getCameraType() != GameCamera::Camera_Type::FirstPerson)
	{
		camera->resetCamera(GameCamera::Camera_Type::FirstPerson);
		camera->setCameraType(GameCamera::Camera_Type::FirstPerson);
	}

	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_2) && camera->getCameraType() != GameCamera::Camera_Type::Free)
	{
		camera->resetCamera(GameCamera::Camera_Type::Free);
		camera->setCameraType(GameCamera::Camera_Type::Free);

	}
	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_3) && camera->getCameraType() != GameCamera::Camera_Type::ThirdPerson)
	{
		camera->resetCamera(GameCamera::Camera_Type::ThirdPerson);
		camera->setCameraType(GameCamera::Camera_Type::ThirdPerson);
	}
	if (camera->getCameraType() == GameCamera::Camera_Type::Free)
		return;
	vec3 power(0.0);
	auto forward = camera->getLook();
	auto right = camera->getRight();
	forward.y = 0.0f;
	forward = glm::normalize(forward);
	right.y = 0.0f;
	right = glm::normalize(right);
	if (keyState.isKeyDown(MyKeyboard::Keys::KEY_A))
	{
		power -= right;
	}
	else if (keyState.isKeyDown(MyKeyboard::Keys::KEY_D))
	{
		power += right;
	}
	else if (keyState.isKeyDown(MyKeyboard::Keys::KEY_W))
	{
		power += forward;
	}
	else if (keyState.isKeyDown(MyKeyboard::Keys::KEY_S))
	{
		power -= forward;
	}
	if (m_focus != nullptr)
	{
		auto pBT = m_focus->getBTRigidBody();
		if (!pBT)
			return;
		//pBT->setLinearVelocity(btVector3(power.x * 10.0f, power.y * 10.0f, power.z * 10.0f));
		
		//auto originPos = m_focus->getLocalPosition();
		//auto forward = vec3(camera->getViewMat4() * glm::vec4(power, 0.0f));
		power *= 510.0f;
		pBT->applyCentralForce(btVector3(power.x, power.y, power.z));
		DEBUG_VEC3(power);
		//pBT->setLinearVelocity(btVector3(forward.x, forward.y, forward.z));
		//m_focus->setLocalPosition(originPos + forward * dt);
	}
	
}

void BallScene::lateUpdate(float delta)
{
	auto camera = BaseManager::getInstance()->getCamera();
	auto lCamera = BaseManager::getInstance()->getLightCamera();

	if (m_focus != nullptr)
	{
		auto carPos = m_focus->getPosition();
		lCamera->setPosition(vec3(carPos.x, carPos.y + 10.0f, carPos.z - 10.0f));
	}
	// 照相机参数更新
	if (m_focus != nullptr)
	{
		switch (camera->getCameraType())
		{
		case GameCamera::Camera_Type::FirstPerson:

			camera->setPosition(m_focus->getPosition());
			//camera->setRotate(m_focus->getRotate());
			break;
		case GameCamera::Camera_Type::ThirdPerson:
			camera->setFocus(m_focus->getPosition());
			//camera->setRotate(m_pCar->getRotate());
			break;
		default:
			break;
		}

	}

}
