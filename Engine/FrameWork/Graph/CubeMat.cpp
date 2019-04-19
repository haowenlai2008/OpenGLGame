#include "CubeMat.h"
#include "Cube.h"
#include "BaseManager.h"
#include <fstream>
using std::ifstream;
vec3 CubeMat::dotScale = vec3(1.0f);
CubeMat * CubeMat::create(vector<vector<int>>& mat, MatType type)
{
	auto pRet = new(std::nothrow) CubeMat();
	if (pRet && pRet->init())
	{
		switch (type)
		{
		case MatType::vertical:
			for (int i = 0; i < mat.size(); i++)
			{
				for (int j = 0; j < mat[i].size(); j++)
				{
					if (mat[i][j] != 0)
					{
						auto cube = Cube::create(CubeType::withTexAndLight);
						cube->setTexture("awesomeface2.png");
						cube->setScale(dotScale);
						cube->setLocalPosition(vec3(float(j) * dotScale.x, float(mat.size() - i - 1)* dotScale.y, 0.0f));
						pRet->addChild(cube);
					}
				}
			}
			break;
		case MatType::lie:
			for (int i = 0; i < mat.size(); i++)
			{
				for (int j = 0; j < mat[i].size(); j++)
				{
					if (mat[i][j] != 0)
					{
						auto cube = Cube::create(CubeType::withTexAndLight);
						cube->setTexture("awesomeface2.png");
						cube->setScale(dotScale);
						cube->setLocalPosition(vec3(float(j)* dotScale.x, 0.0f, -float(mat.size() - i - 1) * dotScale.z));
						pRet->addChild(cube);
					}
				}
			}
			break;
		default:
			break;
		}
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
	return nullptr;
}
CubeMat* CubeMat::create(vector<vector<vec3> >& mat)
{
	auto pRet = new(std::nothrow) CubeMat();
	if (pRet && pRet->init())
	{
		for (int i = 0; i < mat.size(); i++)
		{
			for (int j = 0; j < mat[i].size(); j++)
			{
				auto cube = Cube::create(CubeType::withTexAndLight);
				cube->setTexture("awesomeface2.png");
				cube->setScale(dotScale);
				cube->setLocalPosition(vec3(mat[i][j].x * dotScale.x, mat[i][j].y * dotScale.y, mat[i][j].z * dotScale.z));
				pRet->addChild(cube);
			}
		}
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
	return nullptr;
}
CubeMat * CubeMat::create(std::string&& file, MatType type)
{
	ifstream infile;
	std::cout << DOT_MAT_PATH + file << std::endl;
	infile.open(DOT_MAT_PATH + file);
	if (!infile.is_open())
	{
		std::cout << "nonono" << std::endl;
	}
	vector<string> mat;
	string str;
	while (infile)//一行行地读
	{
		std::getline(infile, str);
		mat.push_back(str);
		std::cout << str << std::endl;
	}
	infile.close();
	auto pRet = new(std::nothrow) CubeMat();
	setDotScale(vec3(0.3f, 0.6f, 0.3f));
	if (pRet && pRet->init())
	{
		switch (type)
		{
		case MatType::vertical:
			for (int i = 0; i < mat.size(); i++)
			{
				for (int j = 0; j < mat[i].size(); j++)
				{
					if (mat[i][j] != '0')
					{
						auto cube = Cube::create(CubeType::withSkyBox);
						//cube->setTexture("back__.jpg");
						cube->setScale(dotScale);
						cube->setLocalPosition(vec3(float(j) * dotScale.x, float(mat.size() - i - 1)* dotScale.y, 0.0f));
						pRet->addChild(cube);

						auto cube2 = Cube::create(CubeType::withSkyBox);
						//cube2->setTexture("back__.jpg");
						cube2->setScale(dotScale);
						cube2->setLocalPosition(vec3(float(j)* dotScale.x, float(mat.size() - i - 1)* dotScale.y, -1.0f *  dotScale.z));
						pRet->addChild(cube2);
					}
				}
			}
			break;
		case MatType::lie:
			for (int i = 0; i < mat.size(); i++)
			{
				for (int j = 0; j < mat[i].size(); j++)
				{
					if (mat[i][j] != '0')
					{
						auto cube = Cube::create(CubeType::withSkyBox);
						cube->setScale(dotScale);
						cube->setLocalPosition(vec3(float(j) * dotScale.x, 0.0f, -float(mat.size() - i - 1) * dotScale.z));
						pRet->addChild(cube);

						auto cube2 = Cube::create(CubeType::withSkyBox);
						cube2->setScale(dotScale);
						cube2->setLocalPosition(vec3(float(j) * dotScale.x, 1.0f * dotScale.y, -float(mat.size() - i - 1) * dotScale.z));
						pRet->addChild(cube2);
					}
				}
			}
			break;
		default:
			break;
		}
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
	return nullptr;
}

bool CubeMat::init()
{
	return true;
}

void CubeMat::draw()
{
}

void CubeMat::setLightSrc(Node * node)
{
	for (auto* p : childs)
	{
		static_cast<Entity*>(p)->setLightSrc(node);
	}
}



CubeMat::CubeMat()
{
}

CubeMat::~CubeMat()
{
}
