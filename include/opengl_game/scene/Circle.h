#pragma once
#include "opengl_game/scene/Entity.h"
class Circle : public Entity
{
public:
	CREATE_FUNC(Circle);
	ENTITY_CREATE_FUNC(Circle);
	virtual bool init() override;
};

