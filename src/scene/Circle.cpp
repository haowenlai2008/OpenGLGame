#include "Circle.h"

bool Circle::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getCircleData());
	setTexture("container.jpg");

	return true;
}
