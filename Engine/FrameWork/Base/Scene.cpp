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
bool Scene::init()
{
	SkyBox* skyBox = SkyBox::create();
	this->addChild(skyBox);

	Cube* light = Cube::create(CubeType::normal);
	//light->setTexture("container2.png");
	light->setScale(vec3(1.0f, 1.0f, 1.0f));
	light->setLocalPosition(vec3(0.0f, 10.0f, 10.0f));
	light->setLightSrc(light);
	DEBUG_VEC3(light->transform.position);
	this->addChild(light);


	CubeMat* mt = CubeMat::createDirMat("d.txt", MatType::vertical);
	mt->setLightSrc(light);
	this->addChild(mt);


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
