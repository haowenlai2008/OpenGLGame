#include "RP_DeferredRenderPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"

static GLuint quadVAO, quadVBO;		// ��Ļ�ı���
bool RP_DeferredRenderPass::Init()
{
	// һ���Զ�������ν��
	std::vector<float> quadVertices = {
		//positions   // texCoords
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	//����֡����Ĵ���(һ��������)
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quadVertices.size(), quadVertices.begin()._Ptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


	GLuint rbo;
	//����֡����
	BaseManager* bmp = BaseManager::getInstance();
	glGenFramebuffers(1, &RenderManager::globalBuffer.scenePassBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.scenePassBuffer);
	//����һ����ɫ����
	glGenTextures(1, &RenderManager::globleTexture.scenePassTexture);
	glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.scenePassTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderManager::globleTexture.scenePassTexture, 0);
	//Ϊ��Ⱥ�ģ�帽������һ����Ⱦ������� create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bmp->screenWidth, bmp->screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	//����֡���壬�������еĸ��� now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_DeferredRenderPass::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// ��GBuffer����Ȼ��帴�Ƶ�SceneBuffer
	BaseManager* bmp = BaseManager::getInstance();
	float width = bmp->screenWidth;
	float height = bmp->screenHeight;
	glBindFramebuffer(GL_READ_FRAMEBUFFER, RenderManager::globalBuffer.gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, RenderManager::globalBuffer.scenePassBuffer);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.scenePassBuffer);

	// �ر���Ȳ��Ժ����д�룬�������ղ��ָ���GBuffer����Ȼ���
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);	

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);



	BaseManager* baseManager = BaseManager::getInstance();
	MaterialManager* matManager = MaterialManager::getInstance();
	glm::mat4 projection = baseManager->getProjMat4();
	glm::mat4 view = baseManager->getViewMat4();
	glm::mat4 lightSpace = baseManager->getLightSpaceMat4();
	glm::vec3 viewPos = baseManager->getViewPos();
	glm::vec3 lightPos = baseManager->getLightPos();


	auto mat = matManager->getUserMaterialRef("Deferred_Render");
	auto shader = mat.m_Shader.lock();

	shader->use();
	mat.bindUniform();
	shader->setMat4("lightSpaceMatrix", lightSpace);
	shader->setVec3("viewPos", viewPos);
	shader->setVec3("light.position", lightPos);
	shader->setVec3("light.position", lightPos);
	shader->setVec3("light.color", vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// �����д�����Ȳ��ԣ�����պ�
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);	
	// ���ǰ����Ⱦ��պ�
	auto p = RenderManager::getInstance()->skyBox;
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

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_DeferredRenderPass::Release()
{
	return true;
}