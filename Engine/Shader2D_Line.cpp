#include "Shader2D_Line.h"
#include <glm/vec3.hpp>
#include "Shader.h"
void Shader2D_Line::use()
{
	std::shared_ptr<Shader> shader(pShader);
	Shader2D_Component::use();
	shader->setVec3("aColor", getColor());
}

bool Shader2D_Line::init()
{
	
	return true;
}

Shader2D_Line::Shader2D_Line()
{
	setComTypeI(ComponentTypeI::Shader);
	setComTypeII(ComponentTypeII::Shader2D_Line);
	pShader = Shader::getShader("line2D");
	setColor(glm::vec3(0.5, 0.5, 0.9));
}

Shader2D_Line::~Shader2D_Line()
{
}
