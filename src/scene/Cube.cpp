#include "opengl_game/scene/Cube.h"
#include "opengl_game/core/BaseManager.h"
#include "opengl_game/render/SkyBox.h"
#include "opengl_game/render/VertexFactory.h"
using std::endl;
using std::cout;

bool Cube::init()
{
	if (!Entity::init())
		return false;
	setMeshAndBuffer(VertexFactory::getBoxData());
	//addBoxRigidBody();
	return true;
}