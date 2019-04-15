#include "Scene.h"
#include "Cube.h"
bool Scene::init()
{
	Cube* light = Cube::create(CubeType::normal);
	//light->setTexture("container2.png");
	light->setScale(vec3(0.2f, 0.2f, 0.2f));
	light->setLocalPosition(vec3(0.0f, 15.0f, -10.0f));
	DEBUG_VEC3(light->transform.position);
	this->addChild(light);

	Cube* cube = Cube::create(CubeType::withTexAndLight);
	cube->setTexture("container2.png");
	cube->setLightSrc(light);
	cube->setLocalPosition(vec3(0.0f, 0.5f, 0.0f));
	this->addChild(cube);

	Cube* ground = Cube::create(CubeType::withTexAndLight);
	ground->setScale(vec3(10.0f, 0.2f, 10.0f));
	ground->setLocalPosition(vec3(0.0, -0.5f, 0.0f));
	ground->setTexture("container.jpg");
	ground->setLightSrc(light);
	this->addChild(ground);
	std::cout << "Scene init" << std::endl;
	return true;
}
