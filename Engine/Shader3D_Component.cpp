#include "Shader3D_Component.h"
#include "BaseManager.h"
#include "RenderManager.h"
#include "GameCamera.h"
#include "Entity.h"
#include "Shader.h"
void Shader3D_Component::use()
{
	std::shared_ptr<Shader> shader(pShader);
	shader->use();
	BaseManager* baseManager = BaseManager::getInstance();
	glm::mat4 projection = baseManager->getProjMat4();
	glm::mat4 view = baseManager->getViewMat4();
	glm::mat4 model = entity->getModelMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);
}

bool Shader3D_Component::init()
{
	return true;
}
void Shader3D_Component::setTexture(std::string&& src)
{
	std::cout << "aaaa" << std::endl;
}
Shader3D_Component::Shader3D_Component()
{

}

Shader3D_Component::~Shader3D_Component()
{
}