#include "CylinderNoCap.h"

bool CylinderNoCap::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getCylinderNoCapData());
	setTexture("container.jpg");
	
	return true;
}
