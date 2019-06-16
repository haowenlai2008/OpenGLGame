#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
using std::list;
using std::map;
using std::string;
class Node;
class LogicManager
{
public:
	static LogicManager* getInstance();
	void init();
	void update(Node* node, float delta);

	~LogicManager();
private:
	static LogicManager* logicManager;
	static map<string, int> textures;
	LogicManager();
	
};
