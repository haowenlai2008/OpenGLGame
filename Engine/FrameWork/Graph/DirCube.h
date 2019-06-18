#pragma once
#include "Cube.h"
#include <vector>
using std::vector;
class DirCube : public Entity
{
public:
	CREATE_FUNC(DirCube);
	static DirCube* create(CubeType _cubeType, vec3 _target);
	static vector<float> vertex;
	static vector<int> index;
	virtual bool init();
	virtual void draw();
	virtual void update(float delta);
	void setType(CubeType _cubeType);
	DirCube();
	bool isArrive;
	vec3 target;
	virtual ~DirCube();
private:
	CubeType cubeType;
};
