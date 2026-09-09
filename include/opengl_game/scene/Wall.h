#pragma once
#include "opengl_game/scene/Entity.h"
class Wall :
	public Entity
{
public:
	CREATE_FUNC(Wall);
	ENTITY_CREATE_FUNC(Wall);

	virtual bool init();

};

