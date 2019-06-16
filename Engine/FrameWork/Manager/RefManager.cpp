#include "RefManager.h"
#include "Ref.h"

RefManager* RefManager::refManager = nullptr;
RefManager * RefManager::getInstance()
{
	if (!refManager)
	{
		refManager = new(std::nothrow) RefManager();
		std::cout << "RefManager init" << std::endl;
	}
	return refManager;
}

void RefManager::addRef(Ref * ref)
{
	refPool.push_back(ref);
}
void RefManager::init()
{

}
void RefManager::update()
{
	for (auto it = refPool.begin(); it != refPool.end(); ++it)
	{
		if ((*it)->count == 0)
		{
			delete (*it);
			(*it) = nullptr;
			refPool.erase(it);
		}
	}
}

RefManager::RefManager()
{
}


RefManager::~RefManager()
{
	for (auto it = refPool.begin(); it != refPool.end(); ++it)
	{
		delete (*it);
		*it = nullptr;
	}
}
