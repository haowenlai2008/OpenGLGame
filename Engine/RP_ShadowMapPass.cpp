#include "RP_ShadowMapPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"
const GLuint SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
bool RP_ShadowMapPass::Init()
{
	glGenFramebuffers(1, &RenderManager::globalBuffer.shadowMapBuffer);
	glGenTextures(1, &RenderManager::globleTexture.shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.shadowMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.shadowMapBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, RenderManager::globleTexture.shadowMapTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

bool RP_ShadowMapPass::Render()
{
	// °ó¶¨shadowmapµÄbuffer
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.shadowMapBuffer);
	glClear(GL_DEPTH_BUFFER_BIT);

	vec4 clearColor = BaseManager::getInstance()->clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
			auto ent_ptr = dynamic_cast<Entity*>(p);
			auto selfMat = ent_ptr->GetMaterial().lock();
			Material& material = matManager->getSystemMaterialRef("SimpleDepth");
			auto shader = material.m_Shader.lock();
			glm::mat4 model = p->getModelMatrix();
			shader->use();
			shader->setMat4("model", model);
			shader->setMat4("lightSpaceMatrix", lightSpace);
			material.bindUniform();

			p->draw();
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	BaseManager* bmp = BaseManager::getInstance();
	glViewport(0, 0, bmp->screenWidth, bmp->screenHeight);

	return true;
}

bool RP_ShadowMapPass::Release()
{
	return true;
}
