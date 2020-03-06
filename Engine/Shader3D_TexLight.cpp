#include "Shader3D_TexLight.h"
#include "Entity.h"
#include "BaseManager.h"
#include "RenderManager.h"
#include "GameCamera.h"
#include "Shader.h"
void Shader3D_TexLight::use()
{
	Shader3D_Component::use();
	if (entity->getLightSrc())
	{
		std::shared_ptr<Shader> shader(pShader);
		shader->setVec3("light.position", entity->getLightSrc()->getPosition());
		shader->setVec3("viewPos", BaseManager::getInstance()->getCamera()->getPosition());
		shader->setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
		shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		// material properties
		shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader->setFloat("material.shininess", 64.0f);
		glActiveTexture(GL_TEXTURE0);
		if (diffuseMap != 0)
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
	}
}

bool Shader3D_TexLight::init()
{
	
	return true;
}
void Shader3D_TexLight::setTexture(std::string&& src)
{
	setDiffuseMap(RenderManager::getTexture(src));
}

Shader3D_TexLight::Shader3D_TexLight() : diffuseMap(0)
{
	setComTypeI(ComponentTypeI::Shader);
	setComTypeII(ComponentTypeII::Shader3D_TexLight);
	pShader = Shader::getShader("withTexAndLight");
}

Shader3D_TexLight::~Shader3D_TexLight()
{
}
