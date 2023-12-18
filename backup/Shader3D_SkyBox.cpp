#include "Shader3D_SkyBox.h"
#include "Entity.h"
#include "BaseManager.h"
#include "RenderManager.h"
#include "GameCamera.h"
#include "SkyBox.h"
#include "Shader.h"
void Shader3D_SkyBox::use()
{
	std::shared_ptr<Shader> shader(pShader);
	Shader3D_Component::use();
	shader->setVec3("cameraPos", BaseManager::getInstance()->getCamera()->getPosition());
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
	pShader = Shader::getShader("withSkyBox");
}

Shader3D_SkyBox::~Shader3D_SkyBox()
{
}
