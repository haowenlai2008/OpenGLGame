#include "RP_ToneMappingGammaPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"

static GLuint quadVAO, quadVBO, rbo;		// ��Ļ�ı���
bool RP_ToneMappingGammaPass::Init()
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

	//����֡����
	BaseManager* bmp = BaseManager::getInstance();
	glGenFramebuffers(1, &RenderManager::globalBuffer.afterPossprocessBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.afterPossprocessBuffer);
	//���һ����ɫ����
	glGenTextures(1, &RenderManager::globleTexture.afterPossprocessTexture);
	glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.afterPossprocessTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderManager::globleTexture.afterPossprocessTexture, 0);
	//Ϊ��Ⱥ�ģ�帽������һ����Ⱦ������� create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bmp->screenWidth, bmp->screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	//����֡���壬������еĸ��� now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_ToneMappingGammaPass::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	vec4 clearColor = BaseManager::getInstance()->clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	string filterName = "";
	GLuint textureID = RenderManager::globleTexture.afterPossprocessTexture;
	std::weak_ptr<Shader> screenShader = Shader::getFilter("toneMappingGamma");
	auto shader = screenShader.lock();
	shader->use();

	glBindVertexArray(quadVAO);
	shader->setInt("screenTexture", 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	return true;
}

RP_ToneMappingGammaPass::~RP_ToneMappingGammaPass()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}
