#pragma once
#include "Node.h"
#include <iostream>
#include <list>
using std::list;
class RenderManager
{
public:
	static RenderManager* getInstance();
	void init();
	void update(Node* node);
	~RenderManager();
private:
	RenderManager();
	static RenderManager* renderManager;
};
