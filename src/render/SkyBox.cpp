#include "opengl_game/render/SkyBox.h"
#include <iostream>
#include <vector>
#include <string>
#include "opengl_game/core/BaseManager.h"
#include "opengl_game/core/func.h"
#include "opengl_game/render/Shader.h"
#include "opengl_game/render/GameCamera.h"
#include "opengl_game/render/VertexFactory.h"

bool SkyBox::init()
{
	if (!Entity::init())
		return false;
	nodeType = NodeType::Skybox;
	setMeshAndBuffer(VertexFactory::getBoxData());
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


SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}
