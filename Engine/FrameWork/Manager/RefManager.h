#pragma once
#include "Ref.h"
#include <iostream>
#include <list>
using std::list;
class RefManager
{
public:
	static RefManager* getInstance();
	void addRef(Ref* ref);
	void update();
	~RefManager();
private:
	RefManager();
	static RefManager* refManager;
	list<Ref*> refPool;
};
