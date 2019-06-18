#pragma once
#include "Entity.h"
#include <vector>
using std::vector;
enum class MatType
{
	vertical,
	lie
};
class CubeMat : public Entity
{
public:
	CREATE_FUNC(CubeMat);
	LL_STATIC_SYNTHESIZE(vec3, dotScale, DotScale);
	static CubeMat* create(vector<vector<int> >& mat, MatType type);
	static CubeMat* create(vector<vector<vec3> >& mat);
	static CubeMat* create(std::string&& file, MatType type);
	static CubeMat* createDirMat(std::string&& file, MatType type);
	virtual bool init();
	virtual void draw();
	virtual void setLightSrc(Node* node);
	CubeMat();
	virtual ~CubeMat();
};
