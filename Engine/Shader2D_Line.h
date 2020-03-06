#pragma once
#include "Shader2D_Component.h"
class Shader2D_Line : public Shader2D_Component
{
public:
	CREATE_FUNC(Shader2D_Line);
	LL_SYNTHESIZE(glm::vec3, color, Color);//—’…´…Ë÷√
	virtual bool init();
	virtual void use();
	Shader2D_Line();
	~Shader2D_Line();
};
