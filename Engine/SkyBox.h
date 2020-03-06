#pragma once
#include "Entity.h"

class SkyBox : public Entity
{
public:
	CREATE_FUNC(SkyBox);
	static unsigned int loadCubemap(std::string&& sboxName, vector<std::string>& faces);
	static unsigned int getSkyBxCubeMap();
	virtual bool init() override;
	virtual void draw() override;
	virtual void renderParamUpdate() override;
	SkyBox();
	virtual ~SkyBox();
private:
	static unsigned int cubemapTexture;
};
