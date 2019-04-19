#include "RenderManager.h"
#include "Ref.h"
#include "func.h"
#include "Node.h"
#include <map>
RenderManager* RenderManager::renderManager = nullptr;
std::map<string, int> RenderManager::textures;
RenderManager * RenderManager::getInstance()
{
	if (!renderManager)
	{
		renderManager = new(std::nothrow) RenderManager();
		std::cout << "RenderManager init" << std::endl;
	}
	return renderManager;
}

unsigned int RenderManager::getTexture(string& path)
{
	unsigned int result = 0;
	if (textures.find(path) == textures.end())
	{
		LoadTexture(result, path);
		textures.insert(std::pair<string, unsigned int>(path, result));
		return result;
	}
	else
	{
		return textures[path];
	}
	return 0;
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
		if (p->getVisable())
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
