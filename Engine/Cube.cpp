#include "Cube.h"
#include "BaseManager.h"
#include "SkyBox.h"
#include "VertexFactory.h"
using std::endl;
using std::cout;

bool Cube::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getBoxData());
	setTexture("container.jpg");
	return true;
}