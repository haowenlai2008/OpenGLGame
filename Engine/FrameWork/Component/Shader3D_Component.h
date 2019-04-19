#pragma once
#include "Component.h"
#include "Shader.h"
class Shader3D_Component : public Component
{
public:
	CREATE_FUNC(Shader3D_Component);
	virtual bool init();
	virtual void use();
	virtual void setTexture(std::string&& src);
	Shader3D_Component();
	~Shader3D_Component();
protected:
	Shader shader;
};
