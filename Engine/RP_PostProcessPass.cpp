#include "RP_PostProcessPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"
#include "VertexFactory.h"
#include "Mesh.h"

static RenderMode m_Rendermode = RenderMode::Normal;
bool RP_PostProcessPass::Init()
{
	GLuint rbo;
	//创建帧缓冲
	BaseManager* bmp = BaseManager::getInstance();
	glGenFramebuffers(1, &RenderManager::globalBuffer.afterPossprocessBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.afterPossprocessBuffer);
	//添加一个颜色附件
	glGenTextures(1, &RenderManager::globleTexture.afterPossprocessTexture);
	glBindTexture(GL_TEXTURE_2D, RenderManager::globleTexture.afterPossprocessTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderManager::globleTexture.afterPossprocessTexture, 0);
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

bool RP_PostProcessPass::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.afterPossprocessBuffer);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	
	BaseManager::getInstance()->colorClear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	string filterName = "";
	GLuint textureID = 0;
	m_Rendermode = RenderMode::Normal;
	switch (m_Rendermode)
	{
	case RenderMode::Normal:
		filterName = "normal";
		textureID = RenderManager::globleTexture.scenePassTexture;
		break;
	case RenderMode::TestDepthMap:
		filterName = "depthTest";
		textureID = RenderManager::globleTexture.shadowMapTexture;
		break;
	default:
		break;
	}
	std::weak_ptr<Shader> screenShader = Shader::getFilter(std::move(filterName));
	auto shader = screenShader.lock();
	shader->use();
	shader->setInt("screenTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	VertexFactory::getQuadData()->draw();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RP_PostProcessPass::Release()
{

	return true;
}
