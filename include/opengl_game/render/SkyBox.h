#pragma once
#include "Entity.h"

class SkyBox : public Entity
{
public:
	CREATE_FUNC(SkyBox);
	ENTITY_CREATE_FUNC(SkyBox);
	virtual bool init() override;
	virtual void draw() override;
	SkyBox();
	virtual ~SkyBox();
};
