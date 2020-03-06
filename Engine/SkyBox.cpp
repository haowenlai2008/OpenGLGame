#include "SkyBox.h"
#include <iostream>
#include <vector>
#include <string>
#include "BaseManager.h"
#include "func.h"
#include "Shader.h"
#include "GameCamera.h"
#include "VertexFactory.h"
using std::vector;
unsigned int SkyBox::cubemapTexture = -1;
unsigned int SkyBox::loadCubemap(std::string&& sboxName, vector<std::string>& faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load((TEXTURE_PATH + sboxName + faces[i]).c_str(), 
			&width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
static vector<std::string> faces
{
	"/right.jpg",
	"/left.jpg",
	"/top.jpg",
	"/bottom.jpg",
	"/front.jpg",
	"/back.jpg"
};
//¶ÁÈ¡Ìì¿ÕºÐÎÆÀí
unsigned int SkyBox::getSkyBxCubeMap()
{
	if (cubemapTexture == -1)
		cubemapTexture = loadCubemap(SKY_BOX, faces);
	return cubemapTexture;
}

bool SkyBox::init()
{
	m_Shader = Shader::getShader("SkyBox");
	cubemapTexture = getSkyBxCubeMap();
	setMeshAndBuffer(VertexFactory::getSphereData());
	
	return true;
}

void SkyBox::draw()
{
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_VertexNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
}

void SkyBox::renderParamUpdate()
{
	if (m_Shader.expired())
		return;
	auto shader = m_Shader.lock();
	shader->use();
	shader->setInt("skybox", 0);
	BaseManager* baseManager = BaseManager::getInstance();
	glm::mat4 projection = baseManager->getProjMat4();	// ²Ã¼ô¾ØÕó
	glm::mat4 view = glm::mat4(glm::mat3(baseManager->getViewMat4()));	// ¹Û²ì¾ØÕó,È¥µôÆ½ÒÆ·ÖÁ¿
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}
