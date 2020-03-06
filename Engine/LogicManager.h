#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
#include "Singleton.h"
using std::list;
using std::map;
using std::string;
class Node;
class LogicManager : public Singleton<LogicManager>
{
public:
	friend class Singleton<LogicManager>;
	void init();
	void update(Node* node, float delta);
	void lateUpdate(Node* node, float delta);
private:
	static map<string, int> textures;
};
