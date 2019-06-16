#include "RenderManager.h"
#include "BaseManager.h"
#include "Ref.h"
#include "func.h"
#include "Node.h"
#include <map>
RenderManager* RenderManager::renderManager = nullptr;
std::map<string, int> RenderManager::textures;

vector<float> RenderManager::quadVertices = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	 //positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};
RenderManager * RenderManager::getInstance()
{
	if (!renderManager)
	{
		renderManager = new(std::nothrow) RenderManager();
		std::cout << "RenderManager init" << std::endl;
	}
	return renderManager;
}

unsigned int RenderManager::getTexture(string& path)
{
	unsigned int result = 0;
	if (textures.find(path) == textures.end())
	{
		LoadTexture(result, path);
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
	filterInit();
}
//�˾���ʼ��(����֡����)
void RenderManager::filterInit()
{
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

	screenShader = Shader::getFilter("sharpen");
	screenShader.use();
	screenShader.setInt("screenTexture", 0);
	//����֡����
	BaseManager* bmp = BaseManager::getInstance();
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//���һ����ɫ����
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->screenWidth, bmp->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//Ϊ��Ⱥ�ģ�帽������һ����Ⱦ������� create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bmp->screenWidth, bmp->screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	//����֡���壬������еĸ��� now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}


void RenderManager::update(Node * node)
{
	if (node == nullptr)
		return;
	for (auto* p : node->childs)
	{
		if (p->getVisable())
			p->draw();
		update(p);
	}
		
}

void RenderManager::bindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void RenderManager::filterUse()
{
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader.use();
	//screenShader.setFloat("saturation", BaseManager::getInstance()->saturation);
	//screenShader.setFloat("contrast", BaseManager::getInstance()->contrast);
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}



RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}
