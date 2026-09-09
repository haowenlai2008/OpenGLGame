#include "opengl_game/scene/Wall.h"

#include "opengl_game/core/BaseManager.h"
#include "opengl_game/render/VertexFactory.h"
using std::endl;
using std::cout;

bool Wall::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getBoxData());
	setTexture("container.jpg");
	addBoxRigidBody(20.0f, 3.0f, 2.0f);
	return true;
}
