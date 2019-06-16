#include "Scene.h"
#include "SkyBox.h"
#include "Cube.h"
#include "CubeMat.h"
#include "Maze.h"
#include "DirCube.h"
#include "PerlinGround.h"
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

	//DirCube* aaa = DirCube::create(CubeType::withLight, vec3(0.0f, 0.0f, -20.0f));
	////light->setTexture("container2.png");
	//aaa->setLightSrc(light);
	//aaa->setLocalPosition(vec3(0.0f, 1.0f, 1.0f));
	//DEBUG_VEC3(aaa->transform.position);
	//this->addChild(aaa);

	//Cube* bb = Cube::create(CubeType::withTexture);
	//bb->setTexture("container2.png");
	//bb->setLightSrc(light);
	//bb->setLocalPosition(vec3(0.0f, 5.0f, 1.0f));

	//DEBUG_VEC3(bb->transform.position);
	//this->addChild(bb);

	CubeMat* mt = CubeMat::createDirMat("f.txt", MatType::vertical);
	for (auto child : mt->childs)
		child->setRotate(vec3(-40.0f, 0.0f, 0.0f));
	mt->setLightSrc(light);
	this->addChild(mt);

	//Cube* cb = Cube::create(CubeType::withTexAndLight);
	//cb->setTexture("back__.jpg");
	//cb->setLightSrc(light);
	
	//this->addChild(cb);
	return true;
}
