#include "Shader3D_SkyBox.h"
#include "Entity.h"
#include "BaseManager.h"
#include "RenderManager.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Shader.h"
void Shader3D_SkyBox::use()
{
	Shader3D_Component::use();
	shader->setVec3("cameraPos", BaseManager::getCamera()->Position);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBox::getSkyBxCubeMap());
}

bool Shader3D_SkyBox::init()
{
	
	return true;
}
void Shader3D_SkyBox::setTexture(std::string&& src)
{
	diffuseMap = RenderManager::getTexture(src);
}
Shader3D_SkyBox::Shader3D_SkyBox() : diffuseMap(0)
{
	setComTypeI(ComponentTypeI::Shader);
	setComTypeII(ComponentTypeII::Shader3D_SkyBox);
	shader = Shader::getShader("withSkyBox");
}

Shader3D_SkyBox::~Shader3D_SkyBox()
{
}
