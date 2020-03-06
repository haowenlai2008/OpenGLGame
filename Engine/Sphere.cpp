#include "Sphere.h"

bool Sphere::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getSphereData());
	setTexture("container2.png");
	return true;
}
