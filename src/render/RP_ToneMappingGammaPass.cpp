#include "RP_ToneMappingGammaPass.h"
#include "RenderManager.h"
#include "BaseManager.h"
#include "Material.h"
#include "Entity.h"
#include "MaterialManager.h"
#include "VertexFactory.h"
#include "Mesh.h"

bool RP_ToneMappingGammaPass::Init()
{
    return true;
}

bool RP_ToneMappingGammaPass::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	BaseManager::getInstance()->colorClear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint textureID = RenderManager::globleTexture.afterPossprocessTexture;
	std::shared_ptr<Shader> shader = Shader::getFilter("toneMappingGamma");
	shader->use();
	shader->setInt("screenTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	VertexFactory::getQuadData()->draw();
	return true;
}

bool RP_ToneMappingGammaPass::Release()
{
	return true;
}
