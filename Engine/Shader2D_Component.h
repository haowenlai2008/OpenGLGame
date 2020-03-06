#pragma once
#include "Component.h"
class Shader;
class Shader2D_Component : public Component
{
public:
	CREATE_FUNC(Shader2D_Component);
	virtual bool init();
	virtual void use();
	virtual void setTexture(std::string&& src);
	Shader2D_Component();
	~Shader2D_Component();
protected:
	std::weak_ptr<Shader> pShader;
};
