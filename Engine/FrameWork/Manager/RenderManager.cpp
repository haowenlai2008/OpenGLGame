#include "RenderManager.h"
#include "Ref.h"

RenderManager* RenderManager::renderManager = nullptr;
RenderManager * RenderManager::getInstance()
{
	if (!renderManager)
	{
		renderManager = new(std::nothrow) RenderManager();
		std::cout << "RenderManager init" << std::endl;
	}
	return renderManager;
}

void RenderManager::init()
{
}


void RenderManager::update(Node * node)
{
	if (node == nullptr)
		return;
	for (auto* p : node->childs)
	{
		p->draw();
		update(p);
	}
		
}



RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}
