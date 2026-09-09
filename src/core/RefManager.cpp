#include "RefManager.h"
#include "Ref.h"

void RefManager::addRef(Ref * ref)
{
	for (auto*& p : refPool)
	{
		if (p == nullptr)
		{
			p = ref;
			return;
		}
	}
	refPool.push_back(ref);
}

void RefManager::init()
{
}

void RefManager::update()
{
	for (auto it = refPool.begin(); it != refPool.end(); ++it)
	{
		if ((*it) != nullptr && (*it)->count == 0)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
}



RefManager::~RefManager()
{
	for (auto it = refPool.begin(); it != refPool.end(); ++it)
	{
		delete (*it);
		*it = nullptr;
	}
}
