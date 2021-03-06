#include "Scene.h"
#include "SkyBox.h"
#include "Cube.h"
#include "CubeMat.h"
#include "Maze.h"
#include "DirCube.h"
#include "PerlinGround.h"
#include "Line2D.h"
#include "Line2D_color_balance.h"
#include "Line2D_BSpline.h"
#include "Car.h"
#include "BaseManager.h"
#include "GameCamera.h"
#include "LightCamera.h"
#include "Ground.h"
#include "Sphere.h"
#include "Cube.h"
bool Scene::init()
{
	//SkyBox* skyBox = SkyBox::create();
	//this->addChild(skyBox);

	//Ground* gnd = Ground::create(Entity_Type::WithTexAndLight);
	//this->addChild(gnd);
	Cube* cube = Cube::create(Entity_Type::TextureCube);
	cube->setTexture("back__.jpg");
	this->addChild(cube);

	m_pCar = Car::create();
	this->addChild(m_pCar);

	return true;
}

void Scene::update(float dt)
{
	auto camera = BaseManager::getInstance()->getCamera();
	// 切换摄像机的逻辑
	auto pBM = BaseManager::getInstance();
	if (pBM->getKeyboardState().isKeyDown(MyKeyboard::Keys::KEY_1) && camera->getCameraType() != GameCamera::Camera_Type::FirstPerson)
	{
		camera->resetCamera(GameCamera::Camera_Type::FirstPerson);
		camera->setCameraType(GameCamera::Camera_Type::FirstPerson);
	}

	if (pBM->getKeyboardState().isKeyDown(MyKeyboard::Keys::KEY_2) && camera->getCameraType() != GameCamera::Camera_Type::Free)
	{
		camera->resetCamera(GameCamera::Camera_Type::Free);
		camera->setCameraType(GameCamera::Camera_Type::Free);

	}
	if (pBM->getKeyboardState().isKeyDown(MyKeyboard::Keys::KEY_3) && camera->getCameraType() != GameCamera::Camera_Type::ThirdPerson)
	{
		camera->resetCamera(GameCamera::Camera_Type::ThirdPerson);
		camera->setCameraType(GameCamera::Camera_Type::ThirdPerson);
	}
}

void Scene::lateUpdate(float delta)
{
	auto camera = BaseManager::getInstance()->getCamera();
	auto lCamera = BaseManager::getInstance()->getLightCamera();

	if (m_pCar != nullptr)
	{
		auto carPos = m_pCar->getHeadPos();
		lCamera->setPosition(vec3(carPos.x, carPos.y + 10.0f, carPos.z - 10.0f));
	}
	// 照相机参数更新
	if (m_pCar != nullptr)
	{
		switch (camera->getCameraType())
		{
		case GameCamera::Camera_Type::FirstPerson:

			camera->setPosition(m_pCar->getHeadPos());
			camera->setRotate(m_pCar->getRotate());
			break;
		case GameCamera::Camera_Type::ThirdPerson:
			camera->setFocus(m_pCar->getCenter());
			//camera->setRotate(m_pCar->getRotate());
			break;
		default:
			break;
		}

	}
	else
	{
		camera->resetCamera(GameCamera::Camera_Type::Free);
	}

}
