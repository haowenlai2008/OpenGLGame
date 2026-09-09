#pragma once
#include "opengl_game/scene/Entity.h"
class ModelNode : public Entity
{
public:
	CREATE_FUNC(ModelNode);
	ENTITY_CREATE_FUNC(ModelNode);
	virtual bool init() override;
};

