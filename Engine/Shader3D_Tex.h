#pragma once
#include "Shader3D_Component.h"
class Shader3D_Tex : public Shader3D_Component
{
public:
	CREATE_FUNC(Shader3D_Tex);
	LL_SYNTHESIZE(glm::vec3, color, Color);//—’…´…Ë÷√
	LL_SYNTHESIZE(unsigned int, diffuseMap, DiffuseMap);
	virtual void setTexture(std::string&& src);
	virtual bool init();
	virtual void use();
	Shader3D_Tex();
	~Shader3D_Tex();
};
