#pragma once
#include "Shader3D_Component.h"
#include "Shader.h"
class Shader3D_Light : public Shader3D_Component
{
public:
	CREATE_FUNC(Shader3D_Light);
	LL_SYNTHESIZE(glm::vec3, color, Color);//��ɫ����
	virtual bool init();
	virtual void use();
	Shader3D_Light();
	~Shader3D_Light();
};
