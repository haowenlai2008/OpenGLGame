#include "Shader3D_normal.h"
#include <glm/vec3.hpp>

void Shader3D_normal::use()
{
	
	Shader3D_Component::use();
	shader->setVec3("aColor", getColor());
}

bool Shader3D_normal::init()
{
	
	return true;
}

Shader3D_normal::Shader3D_normal()
{
	setComTypeI(ComponentTypeI::Shader);
	setComTypeII(ComponentTypeII::Shader3D_normal);
	shader = Shader::getShader("normal");
	setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

Shader3D_normal::~Shader3D_normal()
{
}
