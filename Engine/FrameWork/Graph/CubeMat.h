#pragma once
#include "Entity.h"
#include <vector>
using std::vector;
class CubeMat : public Entity
{
public:
	CREATE_FUNC(CubeMat);
	static CubeMat* create(vector<vector<int> >& mat);
	virtual bool init();
	virtual void draw();
	virtual void setLightSrc(Node* node);
	CubeMat();
	virtual ~CubeMat();
};
