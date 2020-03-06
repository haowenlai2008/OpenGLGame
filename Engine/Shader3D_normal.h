#pragma once
#include "Shader3D_Component.h"
#include "Shader.h"
class Shader3D_normal : public Shader3D_Component
{
public:
	CREATE_FUNC(Shader3D_normal);
	LL_SYNTHESIZE(glm::vec3, color, Color);//—’…´…Ë÷√
	virtual bool init();
	virtual void use();
	Shader3D_normal();
	~Shader3D_normal();
};
