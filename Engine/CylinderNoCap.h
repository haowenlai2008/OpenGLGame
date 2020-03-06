#pragma once
#include "Entity.h"
class CylinderNoCap : public Entity
{
public:
	CREATE_FUNC(CylinderNoCap);
	ENTITY_CREATE_FUNC(CylinderNoCap);
	virtual bool init() override;
};

