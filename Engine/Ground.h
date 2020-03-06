#pragma once
#include "Entity.h"
class Ground : public Entity
{
public:
	CREATE_FUNC(Ground);
	ENTITY_CREATE_FUNC(Ground);
	virtual bool init() override;
};

