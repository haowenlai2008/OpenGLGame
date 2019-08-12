#pragma once
#include "Shader3D_Component.h"
class Shader3D_SkyBox : public Shader3D_Component
{
public:
	CREATE_FUNC(Shader3D_SkyBox);
	LL_SYNTHESIZE(unsigned int, diffuseMap, DiffuseMap);
	virtual bool init();
	virtual void use();
	virtual void setTexture(std::string&& src);
	Shader3D_SkyBox();
	~Shader3D_SkyBox();
};
