#pragma once
#include "Entity.h"
#include <vector>
using std::vector;
enum class CubeType
{
	normal,
	withLight,
	withTexture,
	withTexAndLight,
	withSkyBox
};
class Cube : public Entity
{
public:
	CREATE_FUNC(Cube);
	ENTITY_CREATE_FUNC(Cube);
	//static Cube* create(CubeType _cubeType);
	//static vector<float> vertex;
	//static vector<int> index;
	virtual bool init();
	//virtual void draw();
	//virtual void update(float delta);
//	void setType(CubeType _cubeType);
//	Cube();
//	virtual ~Cube();
//private:
//	CubeType cubeType;
};
