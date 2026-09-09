#pragma once
#include <iostream>
#include <vector>
using std::vector;
class Maze
{
public:
	Maze();
	~Maze();
	void buildMaze(int size);
	void digMaze(int x, int y);
	vector<vector<int> > mat;
private:

};