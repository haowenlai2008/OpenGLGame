#pragma once
#include "Entity.h"

class SkyBox : public Entity
{
public:
	CREATE_FUNC(SkyBox);
	virtual bool init();
	virtual void draw();
	SkyBox();
	virtual ~SkyBox();
private:
	unsigned int cubemapTexture;
};
