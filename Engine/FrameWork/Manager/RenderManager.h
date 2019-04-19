#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
using std::list;
using std::map;
using std::string;
class Node;
class RenderManager
{
public:
	static RenderManager* getInstance();
	static unsigned int getTexture(string& path);
	void init();
	void update(Node* node);

	~RenderManager();
private:
	static RenderManager* renderManager;
	static map<string, int> textures;
	RenderManager();
	
};
