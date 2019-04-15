#pragma once
#include "Node.h"
#include <vector>
using std::vector;
enum class CubeType
{
	normal,
	withLight,
	withTexture,
	withTexAndLight
};
class Cube : public Node
{
public:
	CREATE_FUNC(Cube);
	static Cube* create(CubeType _cubeType);
	static vector<float> vertex;
	static vector<int> index;
	virtual bool init();
	virtual void draw();
	void setType(CubeType _cubeType);
	void setLightSrc(Node* node);
	void setTexture(std::string src);
	Cube();
	virtual ~Cube();
private:
	CubeType cubeType;
	Node* lightSrc;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int diffuseMap;
};
