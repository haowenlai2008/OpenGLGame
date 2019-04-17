#pragma once
#include "Entity.h"

class SkyBox : public Entity
{
public:
	CREATE_FUNC(SkyBox);
	static unsigned int loadCubemap(std::string&& sboxName, vector<std::string> faces);
	static unsigned int getSkyBxCubeMap();
	virtual bool init();
	virtual void draw();
	SkyBox();
	virtual ~SkyBox();
private:
	static unsigned int cubemapTexture;
};
