#include "opengl_game/render/RP_ToneMappingGammaPass.h"
#include "opengl_game/render/RenderManager.h"
#include "opengl_game/core/BaseManager.h"
#include "opengl_game/render/Material.h"
#include "opengl_game/scene/Entity.h"
#include "opengl_game/render/MaterialManager.h"
#include "opengl_game/render/VertexFactory.h"
#include "opengl_game/render/Mesh.h"

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
