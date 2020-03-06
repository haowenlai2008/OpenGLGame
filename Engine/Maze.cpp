#include "Maze.h"
#include <algorithm>
Maze::Maze()
{
	buildMaze(20);
}

Maze::~Maze()
{
}

void Maze::buildMaze(int size)
{
	for (int i = 0; i < size; i++)
	{
		mat.push_back(vector<int>());
		for (int j = 0; j < size; j++)
		{
			mat[i].push_back(1);
		}
	}
	digMaze(1, 1);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << mat[i][j];
		}
		std::cout << std::endl;
	}
}

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };
vector<int> randNum{ 0,1,2,3 };
void Maze::digMaze(int x, int y)
{
	int size = mat.size();
	if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
		return;

	mat[x][y] = 0;
	std::random_shuffle(randNum.begin(), randNum.end());
	for (auto num : randNum)
	{
		switch (num)
		{
		case 0:
			if (x < size - 2 &&
				mat[x + 2][y] != 0 &&
				mat[x + 1][y] != 0 &&
				mat[x + 1][y - 1] != 0 &&
				mat[x + 1][y + 1] != 0)
				digMaze(x + 1, y);
			break;
		case 1:
			if (x > 1 &&
				mat[x - 2][y] != 0 &&
				mat[x - 1][y] != 0 &&
				mat[x - 1][y - 1] != 0 &&
				mat[x - 1][y + 1] != 0)
				digMaze(x - 1, y);
			break;
		case 2:
			if(y < size - 2 &&
				mat[x][y + 2] != 0 &&
				mat[x][y + 1] != 0 &&
				mat[x + 1][y + 1] != 0 &&
				mat[x - 1][y + 1] != 0)
				digMaze(x, y + 1);
			break;
		case 3:
			if (y > 1 &&
				mat[x][y - 2] != 0 &&
				mat[x][y - 1] != 0 &&
				mat[x + 1][y - 1] != 0 &&
				mat[x - 1][y - 1] != 0)
				digMaze(x, y - 1);
			break;
		default:
			break;
		}
	}
	
}
