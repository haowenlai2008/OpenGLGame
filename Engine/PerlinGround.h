#pragma once
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
using std::vector;
using glm::vec3;
class PerlinGround
{
public:
	PerlinGround();
	~PerlinGround();
	void buildMaze(int size);
	vector<vector<vec3> > mat;
private:

};