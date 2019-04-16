#include "CubeMat.h"
#include "Cube.h"
#include "BaseManager.h"

CubeMat * CubeMat::create(vector<vector<int>>& mat)
{
	auto pRet = new(std::nothrow) CubeMat();
	if (pRet && pRet->init())
	{
		for (int i = 0; i < mat.size(); i++)
		{
			for (int j = 0; j < mat[i].size(); j++)
			{
				if (mat[i][j] != 0)
				{
					auto cube = Cube::create(CubeType::withLight);
					cube->setLocalPosition(vec3(float(j), -float(i), 0.0f));
					cube->setScale(vec3(0.1f, 0.2f, 0.2f));
					pRet->addChild(cube);
				}
			}
		}
		pRet->setLocalPosition(vec3(0.0f, float(mat.size()), 0.0f));
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
