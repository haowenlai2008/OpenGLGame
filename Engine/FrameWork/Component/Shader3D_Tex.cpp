#include "Shader3D_Tex.h"
#include "RenderManager.h"
#include "Shader.h"
void Shader3D_Tex::use()
{
	Shader3D_Component::use();
	if (diffuseMap != 0)
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
}

bool Shader3D_Tex::init()
{
	
	return true;
}
void Shader3D_Tex::setTexture(std::string&& src)
{
	diffuseMap = RenderManager::getTexture(src);
}
Shader3D_Tex::Shader3D_Tex()
{
	setComTypeI(ComponentTypeI::Shader);
	setComTypeII(ComponentTypeII::Shader3D_Tex);
	pShader = Shader::getShader("withTexture");
}

Shader3D_Tex::~Shader3D_Tex()
{
}
