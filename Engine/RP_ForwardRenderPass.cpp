#include "RP_ForwardRenderPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"
bool RP_ForwardRenderPass::Init()
{
	GLuint rbo;
	//创建帧缓冲
	BaseManager* bmp = BaseManager::getInstance();
	glGenFramebuffers(1, &RenderManager::globalBuffer.scenePassBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.scenePassBuffer);
	//添加一个颜色附件
	glGenTextures(1, &RenderManager::globleTexture.scenePassTexture);
	glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.scenePassTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderManager::globleTexture.scenePassTexture, 0);
	//为深度和模板附件创建一个渲染缓冲对象 create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bmp->screenWidth, bmp->screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	//创建帧缓冲，添加所有的附件 now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_ForwardRenderPass::Render()
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

	// 前向渲染中天空盒直接当普通的节点渲染都行
	RenderManager::getInstance()->drawObjects.push_back(RenderManager::getInstance()->skyBox);
	for (auto p : RenderManager::getInstance()->drawObjects)
	{
		if (p != nullptr && p->count != 0)
		{
			auto ent_ptr = dynamic_cast<Entity*>(p);
			auto& material = *ent_ptr->GetMaterial().lock();
			auto shader = material.m_Shader.lock();
			glm::mat4 model = p->getModelMatrix();
			shader->use();
			material.bindUniform();
			shader->setMat4("projection", projection);
			shader->setMat4("view", view);
			shader->setMat4("model", model);
			shader->setMat4("lightSpaceMatrix", lightSpace);
			shader->setVec3("viewPos", viewPos);
			shader->setVec3("light.position", lightPos);
			shader->setVec3("light.color", vec3(1.0f, 1.0f, 1.0f));
			p->draw();
		}
	}


    return true;

}

RP_ForwardRenderPass::~RP_ForwardRenderPass()
{
}
