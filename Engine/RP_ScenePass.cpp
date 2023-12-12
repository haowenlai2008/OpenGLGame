#include "RP_ScenePass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"
bool RP_ScenePass::Init()
{

    return true;
}

bool RP_ScenePass::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.scenePassBuffer);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);

	vec4 clearColor = BaseManager::getInstance()->clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	BaseManager* baseManager = BaseManager::getInstance();
	MaterialManager* matManager = MaterialManager::getInstance();
	glm::mat4 projection = baseManager->getProjMat4();
	glm::mat4 view = baseManager->getViewMat4();
	glm::mat4 lightSpace = baseManager->getLightSpaceMat4();
	glm::vec3 viewPos = baseManager->getViewPos();
	glm::vec3 lightPos = baseManager->getLightPos();
	GLuint shadowMap = RenderManager::globleTexture.shadowMapTexture;
	GLuint envMap = RenderManager::globleTexture.environmentMapIBL;
	for (auto p : RenderManager::getInstance()->drawObjects)
	{
		if (p != nullptr && p->count != 0)
		{
			auto ent_ptr = static_cast<Entity*>(p);
			auto& material = *ent_ptr->GetMaterial().lock();
			auto shader = material.m_Shader.lock();
			glm::mat4 model = p->getModelMatrix();
			shader->use();
			shader->setMat4("projection", projection);
			shader->setMat4("view", view);
			shader->setMat4("model", model);
			shader->setMat4("lightSpaceMatrix", lightSpace);
			shader->setVec3("viewPos", viewPos);
			shader->setVec3("light.position", lightPos);

			//if (material.castShadow && shadowMap != -1)
			//{
			//	material.setTextureCacheID("shadowMap", shadowMap);
			//}
			//if (material.requireEnvironmentMap && envMap != -1)
			//{
			//	material.setTextureCacheID("environmentMap", envMap);
			//}
			material.bindUniform();
			p->draw();
		}
	}
    return true;

}
