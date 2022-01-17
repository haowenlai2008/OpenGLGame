#include "SkyBox.h"
#include <iostream>
#include <vector>
#include <string>
#include "BaseManager.h"
#include "func.h"
#include "Shader.h"
#include "GameCamera.h"
#include "VertexFactory.h"

bool SkyBox::init()
{
	if (!Entity::init())
		return false;
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

//void SkyBox::renderParamUpdate()
//{
//	if (m_Shader.expired())
//		return;
//	auto shader = m_Shader.lock();
//	shader->use();
//	
//	BaseManager* baseManager = BaseManager::getInstance();
//	glm::mat4 projection = baseManager->getProjMat4();	// ²Ã¼ô¾ØÕó
//	glm::mat4 view = glm::mat4(glm::mat3(baseManager->getViewMat4()));	// ¹Û²ì¾ØÕó,È¥µôÆ½ÒÆ·ÖÁ¿
//	shader->setMat4("projection", projection);
//	shader->setMat4("view", view);
//	shader->setInt("skybox", 0);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//}

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}
