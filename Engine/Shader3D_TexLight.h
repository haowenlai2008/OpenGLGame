#pragma once
#include "Shader3D_Component.h"
class Shader3D_TexLight : public Shader3D_Component
{
public:
	CREATE_FUNC(Shader3D_TexLight);
	LL_SYNTHESIZE(glm::vec3, color, Color);//—’…´…Ë÷√
	LL_SYNTHESIZE(unsigned int, diffuseMap, DiffuseMap);
	virtual bool init();
	virtual void use();
	virtual void setTexture(std::string&& src);
	Shader3D_TexLight();
	~Shader3D_TexLight();
};
