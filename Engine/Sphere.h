#pragma once
#include "Entity.h"
class Sphere :
	public Entity
{
public:
	CREATE_FUNC(Sphere);
	ENTITY_CREATE_FUNC(Sphere);
	virtual bool init() override;
};

