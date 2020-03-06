#include "Shader3D_Light.h"
#include "Entity.h"
#include "BaseManager.h"
#include "GameCamera.h"
#include "Shader.h"
void Shader3D_Light::use()
{
	Shader3D_Component::use();
	if (entity->getLightSrc())
	{
		std::shared_ptr<Shader> shader(pShader);
		shader->setVec3("objectColor", getColor());
		shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		shader->setVec3("lightPos", entity->getLightSrc()->getPosition());
		shader->setVec3("viewPos", BaseManager::getInstance()->getCamera()->getPosition());
	}
}

bool Shader3D_Light::init()
{
	
	return true;
}

Shader3D_Light::Shader3D_Light()
{
	setComTypeI(ComponentTypeI::Shader);
	setComTypeII(ComponentTypeII::Shader3D_Light);
	pShader = Shader::getShader("withLight");
	setColor(vec3(1.0f, 1.0f, 1.0f));
}

Shader3D_Light::~Shader3D_Light()
{
}
