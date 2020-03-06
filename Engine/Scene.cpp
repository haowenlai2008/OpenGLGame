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
bool Scene::init()
{
	SkyBox* skyBox = SkyBox::create();
	this->addChild(skyBox);

	//Cube* light = Cube::create(Entity_Type::WithTex);
	////light->setTexture("container2.png");
	//light->setScale(vec3(1.0f, 1.0f, 1.0f));
	//light->setLocalPosition(vec3(0.0f, 10.0f, 10.0f));
	////light->setLightSrc((Node*)light);
	//DEBUG_VEC3(light->transform.position);
	//this->addChild(light);

	//Cube* HA = Cube::create(Entity_Type::WithTex);
	////HA->setLightSrc((Node*)light);
	//HA->Rotate(vec3(60.0f, 0.0f, 0.0f));
	//this->addChild(HA);
	////CubeMat* mt = CubeMat::createDirMat("d.txt", MatType::vertical);
	////mt->Rotate(vec3(60.0f, 0.0f, 0.0f));
	////mt->setLightSrc(light);
	////Node* node = Node::create();
	////->setPosition(vec3(0.0f, 0.0f, 10.0f));
	//Cube* cube = Cube::create(Entity_Type::WithTex);
	//cube->setPosition(vec3(0.0f, 10.0f, 10.0f));
	//cube->setRotate(vec3(60.0f, 0.0f, 0.0f));
	////cube->setLightSrc((Node*)light);
	////node->addChild(cube);
	//this->addChild(cube);


	m_pCar = Car::create();
	this->addChild(m_pCar);

	Ground* gnd = Ground::create(Entity_Type::WithTex);
	this->addChild(gnd);
	//Line2D* line1 = Line2D::create();
	//Line2D* line2 = Line2D::create();
	//Line2D* line3 = Line2D::create();
	//for (int i = 0; i < 256; i++)
	//{
	//	float value = (float)i / 255.0f;
	//	glm::vec3 weight = Line2D_ColorBalance::transfer(value);
	//	float x = value;
	//	line1->addPoint(glm::vec2(x, weight.r));
	//	line2->addPoint(glm::vec2(x, weight.g));
	//	line3->addPoint(glm::vec2(x, weight.b));
	//}
	//this->addChild(line1);
	//this->addChild(line2);
	//this->addChild(line3);
	//Line2D_BSpline* line = Line2D_BSpline::create();
	//this->addChild(line);
	//vector<int> test = { 1, 2, 3, 4, 5, 6 };
	//for (auto it = test.begin(); it != test.end(); it++)
	//{
	//	if (*it == 3)
	//	{
	//		std::cout << int(it._Ptr) << std::endl;
	//		auto it2 = test.erase(it);
	//		std::cout << int(it2._Ptr) << std::endl;
	//	}
	//}
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
		lCamera->setPosition(vec3(carPos.x, carPos.y + 10.0f, carPos.z + 10.0f));
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
