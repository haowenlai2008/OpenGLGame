#include "RenderManager.h"
#include "Node.h"
#include "RP_IBLPreRenderPass.h"
#include "RP_PostProcessPass.h"
#include "RP_ScenePass.h"
#include "RP_ShadowMapPass.h"
#include "RP_RenderPass.h"

GlobalTextureStructure RenderManager::globleTexture = {
	-1, -1, -1, -1, -1, -1
};

GlobleBufferStructure RenderManager::globalBuffer = {
	-1, -1, -1
};


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
	if (node->getNodeType() == NodeType::Render)
		drawObjects.push_back(node);
}


