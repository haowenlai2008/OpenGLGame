#include "LogicManager.h"
#include <map>
#include <queue>
#include "Ref.h"
#include "func.h"
#include "Node.h"
#include "RenderManager.h"
void LogicManager::init()
{
}

void LogicManager::update(Node * node, float delta)
{
	if (node == nullptr)
		return;

	for (auto*& p : node->childs)
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
	for (auto*& p : node->childs)
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
