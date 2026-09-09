#include "Ground.h"
bool Ground::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getGroundData());
	setTexture("surface.jpg");
	setScale(vec3(5.0f, 1.0f, 5.0f));
	return true;
}
