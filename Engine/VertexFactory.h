#pragma once
#include "func.h"
#include <vector>
using std::vector;
using std::shared_ptr;
class Mesh;
class VertexFactory
{
public:
	static shared_ptr<Mesh> getBoxData();
	static shared_ptr<Mesh> getCircleData();// 圆
	static shared_ptr<Mesh> getCylinderNoCapData();// 圆柱的侧面
	static shared_ptr<Mesh> getCylinderData();// 圆柱
	static shared_ptr<Mesh> getSphereData();// 球
	static shared_ptr<Mesh> getPlaneData();// 平面
	static shared_ptr<Mesh> getTestPlaneData();// 平面
	static shared_ptr<Mesh> getGroundData();// 平面
private:
	static shared_ptr<Mesh> boxData;
	static shared_ptr<Mesh> circleData;
	static shared_ptr<Mesh> cylinderNoCapData;
	static shared_ptr<Mesh> cylinderData;
	static shared_ptr<Mesh> sphereData;
	static shared_ptr<Mesh> planeData;
	static shared_ptr<Mesh> testPlaneData;
	static shared_ptr<Mesh> goundData;
};

