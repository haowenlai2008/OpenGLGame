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
