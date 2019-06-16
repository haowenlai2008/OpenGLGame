#include "LogicManager.h"
#include "Ref.h"
#include "func.h"
#include "Node.h"
#include <map>
LogicManager* LogicManager::logicManager = nullptr;
LogicManager * LogicManager::getInstance()
{
	if (!logicManager)
	{
		logicManager = new(std::nothrow) LogicManager();
		std::cout << "LogicManager init" << std::endl;
	}
	return logicManager;
}
void LogicManager::init()
{
}


void LogicManager::update(Node * node, float delta)
{
	if (node == nullptr)
		return;
	for (auto* p : node->childs)
	{
		if (p->count == 0)
		{
			std::cout << "diu" << std::endl;
			node->childs.erase(std::find(node->childs.begin(), node->childs.end(), p));
			continue;
		}	
		if (p->getVisable())
			p->update(delta);
		update(p, delta);
	}
		
}



LogicManager::LogicManager()
{
}


LogicManager::~LogicManager()
{
}
