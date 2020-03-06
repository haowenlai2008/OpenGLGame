#pragma once
#include <list>
#include "Ref.h"
#include "Singleton.h"
using std::list;
class RefManager : public Singleton<RefManager>
{
public:
	friend class Singleton<RefManager>;
	void addRef(Ref* ref);
	void init();
	void update();
	~RefManager();
private:
	list<Ref*> refPool;
};
