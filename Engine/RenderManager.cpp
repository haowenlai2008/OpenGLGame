#include "RenderManager.h"
#include "BaseManager.h"
#include "Ref.h"
#include "func.h"
#include "Node.h"
#include "Entity.h"
#include "Shader.h"
#include "Cube.h"
#include "Material.h"
#include "MaterialManager.h"
#include "RP_IBLPreRenderPass.h"
#include "RP_PostProcessPass.h"
#include "RP_ScenePass.h"
#include "RP_ShadowMapPass.h"
#include "RP_RenderPass.h"
#include <map>
#include <vector>

using std::vector;
std::map<string, GLuint> RenderManager::textures;

GlobalTextureStructure RenderManager::globleTexture = {
	-1, -1, -1
};

GlobleBufferStructure RenderManager::globalBuffer = {
	-1, -1, -1
};

unsigned int RenderManager::getTexture(string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadTexture(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

unsigned int RenderManager::getTextureByAbsolutePath(string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadTextureByAbsolutePath(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

unsigned int RenderManager::getHDRTexture(string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadHDRTexture(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

unsigned int RenderManager::getCubeTexture(string& path)
{
	unsigned int result = 0;
	if (textures.empty() || textures.find(path) == textures.end())
	{
		ResourceTools::LoadCubemap(result, std::move(path));
		textures.insert(std::pair<string, unsigned int>(path, result));
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
}

void RenderManager::init()
{
	m_RenderPassList =
	{
		std::make_shared<RP_IBLPreRenderPass>(),
		std::make_shared<RP_ShadowMapPass>(),
		std::make_shared<RP_ScenePass>(),
		std::make_shared<RP_PostProcessPass>(),
	};
	for (weak_ptr<RP_RenderPass> rp_wptr : m_RenderPassList)
	{
		rp_wptr.lock().get()->Init();
	}
	//setDepthMap(-1);
	//setEnvMap(-1);
	//setRenderMode(RenderMode::Normal);
	//equirectangularToCubemap();	// 预计算环境贴图
	//filterInit();
	//depthFBOInit();
}

const GLuint SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
void RenderManager::depthFBOInit()
{
	glGenFramebuffers(1, &m_DepthFrameBuffer);
	glGenTextures(1, &m_DepthMap);
	glBindTexture(GL_TEXTURE_2D, m_DepthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//m_SimpleDepthShader = Shader::getShader("simpleDepth");
}

// 环境贴图
void RenderManager::equirectangularToCubemap()
{
	Cube* cb = Cube::create(MaterialType::EquirectangularToCubemap);
	cb->setCullFace(GL_FRONT);
	unsigned int captureFBO, captureRBO;
	glGenFramebuffers(1, &captureFBO);
	glGenRenderbuffers(1, &captureRBO);

	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

	glGenTextures(1, &m_EnvMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_EnvMap);
	for (unsigned int i = 0; i < 6; ++i)
	{
		// note that we store each face with 16 bit floating point values
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
			512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};
	auto material = cb->GetMaterial().lock();
	auto equirectangularToCubemapShader = material->m_Shader.lock();
	equirectangularToCubemapShader->use();
	equirectangularToCubemapShader->setInt("equirectangularMap", 0);
	equirectangularToCubemapShader->setMat4("projection", captureProjection);
	material->bindUniform();

	glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	for (unsigned int i = 0; i < 6; ++i)
	{
		equirectangularToCubemapShader->setMat4("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_EnvMap, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cb->draw(); // renders a 1x1 cube
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	cb->release();
	cb = nullptr;
}
//滤镜初始化(创建帧缓冲)
void RenderManager::filterInit()
{
	// 一次性顶点无所谓了
	vector<float> quadVertices = {
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

	string filterName = "";
	switch (m_Rendermode)
	{
		case RenderMode::Normal:
			filterName = "normal";
			break;
		case RenderMode::TestDepthMap:
			filterName = "depthTest";
			break;
		default:
			break;
	}
	//screenShader = Shader::getFilter("depthTest");
	screenShader = Shader::getFilter(std::move(filterName));
	//创建帧缓冲
	BaseManager* bmp = BaseManager::getInstance();
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//添加一个颜色附件
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//为深度和模板附件创建一个渲染缓冲对象 create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bmp->screenWidth, bmp->screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	//创建帧缓冲，添加所有的附件 now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// 后处理
void RenderManager::postProcess()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto shader = screenShader.lock();
	shader->use();
	glBindVertexArray(quadVAO);

	shader->setInt("screenTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	GLuint bufferId = 0;
	switch (m_Rendermode)
	{
	case RenderMode::Normal:
		bufferId = textureColorbuffer;
		break;
	case RenderMode::TestDepthMap:
		bufferId = m_DepthMap;
		break;
	default:
		break;
	}
	glBindTexture(GL_TEXTURE_2D, bufferId);	// use the color attachment texture as the texture of the quad plane
	//glBindTexture(GL_TEXTURE_2D, m_DepthMap);	// use the color attachment texture as the texture of the quad plane

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderManager::update(Node * node)
{
		
}

// 管线
void RenderManager::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// 先画ShadowMap
	//shadowMapRenderBegin();
	//renderScene();
	//shadowMapRenderEnd();

	//bindFrameBuffer();
	//renderScene();
	//postProcess();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (weak_ptr<RP_RenderPass> rp_wptr : m_RenderPassList)
	{
		rp_wptr.lock().get()->Render();
	}
	auto newList = std::list<Node*>();
	drawObjects.swap(newList);

}

void RenderManager::bindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
}

void RenderManager::addDrawNode(Node* node)
{
	if (node->getNodeType() == NodeType::Render)
		drawObjects.push_back(node);
}

void RenderManager::shadowMapRenderBegin()
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthFrameBuffer);
	glClear(GL_DEPTH_BUFFER_BIT);
	setIsShadow(true);
}

void RenderManager::shadowMapRenderEnd()
{
	setIsShadow(false);
	BaseManager* bmp = BaseManager::getInstance();
	glViewport(0, 0, bmp->screenWidth, bmp->screenHeight);
}

void RenderManager::renderScene()
{
	BaseManager* baseManager = BaseManager::getInstance();
	MaterialManager* matManager = MaterialManager::getInstance();
	glm::mat4 projection = baseManager->getProjMat4();
	glm::mat4 view = baseManager->getViewMat4();
	glm::mat4 lightSpace = baseManager->getLightSpaceMat4();
	glm::vec3 viewPos = baseManager->getViewPos();
	glm::vec3 lightPos = baseManager->getLightPos();
	GLuint shadowMap = getDepthMap();
	GLuint envMap = getEnvMap();
	for (auto p : drawObjects)
	{
		if (p != nullptr && p->count != 0)
		{
			auto ent_ptr = static_cast<Entity*>(p);
			auto selfMat = ent_ptr->GetMaterial().lock();
			Material& material = m_IsShadow ? matManager->getSystemMaterialRef(MaterialType::SimpleDepth) : *selfMat;
			auto shader = material.m_Shader.lock();
			glm::mat4 model = p->getModelMatrix();
			shader->use();
			shader->setMat4("projection", projection);
			shader->setMat4("view", view);
			shader->setMat4("model", model);
			shader->setMat4("lightSpaceMatrix", lightSpace);
			shader->setVec3("viewPos", viewPos);
			shader->setVec3("light.position", lightPos);

			if (material.castShadow && shadowMap != -1)
			{
				//DEBUG_VEC3(lightPos);
				//std::cout << getDepthMap() << std::endl;
				material.setTextureCacheID("shadowMap", shadowMap);
			}
			if (material.requireEnvironmentMap && envMap != -1)
			{
				material.setTextureCacheID("environmentMap", envMap);
			}
			material.bindUniform();

			//if (p->getDebugID() == 100)
			//{
			//	std::cout << "hahahahah" << std::endl;
			//}
			p->draw();
		}
	}
}



std::shared_ptr<Shader> RenderManager::getSimpleDepthShader()
{
	return m_SimpleDepthShader.lock();
}

RenderManager::~RenderManager()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}
