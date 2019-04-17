#include "PerlinGround.h"
#include <algorithm>
#include "Perlin.h"
PerlinGround::PerlinGround()
{
}

PerlinGround::~PerlinGround()
{
}

void PerlinGround::buildMaze(int size)
{
	for (int i = 0; i < size; i++)
	{
		mat.push_back(vector<vec3 >());
		for (int j = 0; j < size; j++)
		{
			mat[i].push_back(vec3(float(i), (int)(Perlin::PerlinNoise(i, j) * 4), float(j)));
		}
	}
}
