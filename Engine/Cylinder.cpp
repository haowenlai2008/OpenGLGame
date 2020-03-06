#include "Cylinder.h"

bool Cylinder::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getCylinderData());
	//setTexture(L"Texture\\WoodCrate.dds");

	return true;
}
