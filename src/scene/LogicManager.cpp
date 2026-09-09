#include "opengl_game/scene/LogicManager.h"
#include "opengl_game/core/func.h"
#include "opengl_game/scene/Node.h"
#include "opengl_game/render/RenderManager.h"
void LogicManager::init()
{
}

void LogicManager::update(Node * node, float delta)
{
	if (node == nullptr)
		return;

	for (auto& p : node->childs)
	{
		if (p == nullptr)
		{
			continue;
		}	
		if (p->count == 0)
		{
			p = nullptr;
			continue;
		}
		
		if (p->getVisable())
		{
			p->update(delta);
			RenderManager::getInstance()->addDrawNode(p);
			update(p, delta);
		}

	}
		
}

void LogicManager::lateUpdate(Node* node, float delta)
{
	if (node == nullptr)
		return;
	for (auto& p : node->childs)
	{
		if (p == nullptr)
		{
			continue;
		}
		if (p->count == 0)
		{
			p = nullptr;
			continue;
		}

		if (p->getVisable())
		{
			p->lateUpdate(delta);
			lateUpdate(p, delta);
		}

	}
}
