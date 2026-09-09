#include "opengl_game/render/ModelNode.h"

bool ModelNode::init()
{
	if (!Entity::init())
		return false;
	return true;
}

