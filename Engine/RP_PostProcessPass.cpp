#include "RP_PostProcessPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"


static RenderMode m_Rendermode = RenderMode::Normal;
static GLuint quadVAO, quadVBO;		// 屏幕四边形
bool RP_PostProcessPass::Init()
{
	// 一次性顶点无所谓了
	std::vector<float> quadVertices = {
		//positions   // texCoords
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	//创建帧缓冲的窗体(一个正方形)
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quadVertices.size(), quadVertices.begin()._Ptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


    return true;
}

bool RP_PostProcessPass::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, RenderManager::globalBuffer.afterPossprocessBuffer);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	vec4 clearColor = BaseManager::getInstance()->clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
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

	glBindVertexArray(quadVAO);
	shader->setInt("screenTexture", 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
    return true;
}

RP_PostProcessPass::~RP_PostProcessPass()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}
