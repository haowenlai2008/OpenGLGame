#pragma once
#include "Entity.h"
class Cylinder : public Entity
{
public:
	CREATE_FUNC(Cylinder);
	ENTITY_CREATE_FUNC(Cylinder);
	virtual bool init() override;
};

