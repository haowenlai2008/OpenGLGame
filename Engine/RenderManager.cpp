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

// 环境贴图
void RenderManager::equirectangularToCubemap()
{
	//Cube* cb = Cube::create(MaterialType::EquirectangularToCubemap);
	//cb->setCullFace(GL_FRONT);
	//unsigned int captureFBO, captureRBO;
	//glGenFramebuffers(1, &captureFBO);
	//glGenRenderbuffers(1, &captureRBO);

	//glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	//glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

	//glGenTextures(1, &m_EnvMap);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, m_EnvMap);
	//for (unsigned int i = 0; i < 6; ++i)
	//{
	//	// note that we store each face with 16 bit floating point values
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
	//		512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
	//}
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	//glm::mat4 captureViews[] =
	//{
	//   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	//   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	//   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
	//   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
	//   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	//   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	//};
	//auto material = cb->GetMaterial().lock();
	//auto equirectangularToCubemapShader = material->m_Shader.lock();
	//equirectangularToCubemapShader->use();
	//equirectangularToCubemapShader->setInt("equirectangularMap", 0);
	//equirectangularToCubemapShader->setMat4("projection", captureProjection);
	//material->bindUniform();

	//glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
	//glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	//for (unsigned int i = 0; i < 6; ++i)
	//{
	//	equirectangularToCubemapShader->setMat4("view", captureViews[i]);
	//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
	//		GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_EnvMap, 0);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	cb->draw(); // renders a 1x1 cube
	//}
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//cb->release();
	//cb = nullptr;
}


// 管线初始化
void RenderManager::init()
{
	m_RenderPassList =
	{
		std::make_shared<RP_IBLPreRenderPass>(),
		std::make_shared<RP_ShadowMapPass>(),
		std::make_shared<RP_ScenePass>(),
		std::make_shared<RP_PostProcessPass>(),
	};
	for (shared_ptr<RP_RenderPass>& rp_ptr : m_RenderPassList)
		rp_ptr->Init();
}

// 管线
void RenderManager::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (shared_ptr<RP_RenderPass>& rp_ptr : m_RenderPassList)
		rp_ptr->Render();
	std::list<Node*>().swap(drawObjects);

}


void RenderManager::addDrawNode(Node* node)
{
	if (node->getNodeType() == NodeType::Render)
		drawObjects.push_back(node);
}


std::shared_ptr<Shader> RenderManager::getSimpleDepthShader()
{
	return m_SimpleDepthShader.lock();
}

