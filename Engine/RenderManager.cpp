#include "RenderManager.h"
#include "Node.h"
#include "RP_IBLPreRenderPass.h"
#include "RP_PostProcessPass.h"
#include "RP_ForwardRenderPass.h"
#include "RP_ShadowMapPass.h"
#include "RP_RenderPass.h"
#include "RP_ToneMappingGammaPass.h"
#include "RP_GBufferPass.h";
#include "RP_DeferredRenderPass.h"
GlobalTextureStructure RenderManager::globleTexture = GlobalTextureStructure();

GlobleBufferStructure RenderManager::globalBuffer = GlobleBufferStructure();


// 管线初始化
void RenderManager::init()
{
	if (false)
	{
		// 前向管线
		m_RenderPassList =
		{
			std::make_shared<RP_IBLPreRenderPass>(),
			std::make_shared<RP_ShadowMapPass>(),
			std::make_shared<RP_ForwardRenderPass>(),
			std::make_shared<RP_PostProcessPass>(),
			std::make_shared<RP_ToneMappingGammaPass>(),
		};
	}
	else
	{
		// 延迟管线
		m_RenderPassList =
		{
			std::make_shared<RP_IBLPreRenderPass>(),
			std::make_shared<RP_ShadowMapPass>(),
			std::make_shared<RP_GBufferPass>(),
			std::make_shared<RP_DeferredRenderPass>(),
			std::make_shared<RP_PostProcessPass>(),
			std::make_shared<RP_ToneMappingGammaPass>(),
		};
	}
	for (std::shared_ptr<RP_RenderPass>& rp_ptr : m_RenderPassList)
		rp_ptr->Init();
}

// 管线
void RenderManager::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (std::shared_ptr<RP_RenderPass>& rp_ptr : m_RenderPassList)
		rp_ptr->Render();
	std::list<Node*>().swap(drawObjects);

}


void RenderManager::addDrawNode(Node* node)
{
	switch (node->getNodeType())
	{
		case NodeType::Render:
			drawObjects.push_back(node);
			break;
		case NodeType::Skybox:
			skyBox = node;
			break;
		default:
			break;
	}
}


