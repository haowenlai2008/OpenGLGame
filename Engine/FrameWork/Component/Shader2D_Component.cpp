#include "Shader2D_Component.h"
#include "BaseManager.h"
#include "RenderManager.h"
#include "Camera.h"
#include "Entity.h"
#include "Shader.h"
void Shader2D_Component::use()
{
	std::shared_ptr<Shader> shader(pShader);
	shader->use();
	glGetError();
	BaseManager* baseManager = BaseManager::getInstance();
	Camera& camera = *baseManager->getCamera();
	glm::mat4 projection = glm::ortho(0.0f, (float)baseManager->screenWidth, (float)baseManager->screenHeight, 0.0f, -1.0f, 1.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 model = entity->getModelMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);
	glGetError();
}

bool Shader2D_Component::init()
{
	return true;
}
void Shader2D_Component::setTexture(std::string&& src)
{
	std::cout << "aaaa" << std::endl;
}
Shader2D_Component::Shader2D_Component()
{

}

Shader2D_Component::~Shader2D_Component()
{
}
