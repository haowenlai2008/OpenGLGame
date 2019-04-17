#include "Scene.h"
#include "SkyBox.h"
#include "Cube.h"
#include "CubeMat.h"
#include "Maze.h"
#include "PerlinGround.h"
bool Scene::init()
{
	SkyBox* skyBox = SkyBox::create();
	this->addChild(skyBox);

	Cube* light = Cube::create(CubeType::normal);
	//light->setTexture("container2.png");
	light->setScale(vec3(0.2f, 0.2f, 0.2f));
	light->setLocalPosition(vec3(0.0f, 100.0f, 10.0f));
	light->setLightSrc(light);
	DEBUG_VEC3(light->transform.position);
	this->addChild(light);

	//Cube* ground2 = Cube::create(CubeType::withTexAndLight);
	//ground2->setTexture("container2.png");
	//ground2->setScale(vec3(20.0f, 0.2f, 20.0f));
	//ground2->setLocalPosition(vec3(0.5f, -5.0f, -0.5));
	//ground2->setLightSrc(light);
	//this->addChild(ground2);

	//Cube* ground = Cube::create(CubeType::withTexAndLight);
	//ground->setTexture("awesomeface.png");
	//ground->setScale(vec3(20.0f, 0.2f, 20.0f));
	//ground->setLocalPosition(vec3(10.0f, -0.8f, -10.0f));
	//ground->setLightSrc(light);
	//this->addChild(ground);

	//CubeMat* txt = CubeMat::create("b.txt", MatType::vertical);
	//txt->setLightSrc(light);
	//txt->setLocalPosition(vec3(-50.0f, 0.0f, 0.0f));
	//this->addChild(txt);

	//Maze maze;
	//CubeMat* mz = CubeMat::create(maze.mat, MatType::lie);
	//mz->setLightSrc(light);
	//this->addChild(mz);
	PerlinGround perlinG;
	perlinG.buildMaze(50);
	CubeMat* pl = CubeMat::create(perlinG.mat);
	pl->setLightSrc(light);
	this->addChild(pl);
	return true;
}
