#include "VertexFactory.h"
#include "Mesh.h"



static float radius = 1.0f;//球面或者圆面的半径
static GLuint slices = 20; //圆或者圆柱的底面的精度
static GLuint levels = 20;//球面的层数
shared_ptr<Mesh> VertexFactory::boxData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::circleData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::cylinderNoCapData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::cylinderData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::sphereData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::planeData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::testPlaneData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::goundData = std::make_shared<Mesh>();
shared_ptr<Mesh> VertexFactory::getBoxData()
{
	if (boxData->vertexData.empty())
	{
		boxData->vertexData.resize(24);
		vector<MeshData>& vertexDataList = boxData->vertexData;
		float w2 = 0.5f;
		float h2 = 0.5f;
		float d2 = 0.5f;
		// 右面(+X面)
		vertexDataList[0].pos = vec3(w2, -h2, d2);
		vertexDataList[1].pos = vec3(w2, h2, d2);
		vertexDataList[2].pos = vec3(w2, h2, -d2);
		vertexDataList[3].pos = vec3(w2, -h2, -d2);
		// 左面(-X面)
		vertexDataList[4].pos = vec3(-w2, -h2, -d2);
		vertexDataList[5].pos = vec3(-w2, h2, -d2);
		vertexDataList[6].pos = vec3(-w2, h2, d2);
		vertexDataList[7].pos = vec3(-w2, -h2, d2);
		// 顶面(+Y面)
		vertexDataList[8].pos = vec3(-w2, h2, d2);
		vertexDataList[9].pos = vec3(-w2, h2, -d2);
		vertexDataList[10].pos = vec3(w2, h2, -d2);
		vertexDataList[11].pos = vec3(w2, h2, d2);
		// 底面(-Y面)
		vertexDataList[12].pos = vec3(w2, -h2, d2);
		vertexDataList[13].pos = vec3(w2, -h2, -d2);
		vertexDataList[14].pos = vec3(-w2, -h2, -d2);
		vertexDataList[15].pos = vec3(-w2, -h2, d2);
		// 背面(+Z面)
		vertexDataList[16].pos = vec3(w2, -h2, -d2);
		vertexDataList[17].pos = vec3(w2, h2, -d2);
		vertexDataList[18].pos = vec3(-w2, h2, -d2);
		vertexDataList[19].pos = vec3(-w2, -h2, -d2);
		// 正面(-Z面)
		vertexDataList[20].pos = vec3(-w2, -h2, d2);
		vertexDataList[21].pos = vec3(-w2, h2, d2);
		vertexDataList[22].pos = vec3(w2, h2, d2);
		vertexDataList[23].pos = vec3(w2, -h2, d2);

		for (GLuint i = 0; i < 4; ++i)
		{
			// 右面(+X面)
			vertexDataList[i].normal = vec3(1.0f, 0.0f, 0.0f);
			// 左面(-X面)
			vertexDataList[i + 4].normal = vec3(-1.0f, 0.0f, 0.0f);
			// 顶面(+Y面)
			vertexDataList[i + 8].normal = vec3(0.0f, 1.0f, 0.0f);
			// 底面(-Y面)
			vertexDataList[i + 12].normal = vec3(0.0f, -1.0f, 0.0f);
			// 背面(+Z面)
			vertexDataList[i + 16].normal = vec3(0.0f, 0.0f, -1.0f);
			// 正面(-Z面)
			vertexDataList[i + 20].normal = vec3(0.0f, 0.0f, 1.0f);
		}

		for (GLuint i = 0; i < 6; ++i)
		{
			vertexDataList[i * 4].tex = vec2(0.0f, 0.0f);
			vertexDataList[i * 4 + 1].tex = vec2(0.0f, 1.0f);
			vertexDataList[i * 4 + 2].tex = vec2(1.0f, 1.0f);
			vertexDataList[i * 4 + 3].tex = vec2(1.0f, 0.0f);
		}
		boxData->indices = {
			2, 1, 0, 0, 3, 2,
			6, 5, 4, 4, 7, 6,
			10, 9, 8, 8, 11, 10,
			14, 13, 12, 12, 15, 14,
			18, 17, 16, 16, 19, 18,
			22, 21, 20, 20, 23, 22
		};
	}
	return boxData;
}

shared_ptr<Mesh> VertexFactory::getCircleData()
{
	if (circleData->vertexData.empty())
	{
		GLuint vertexCount = ::slices + 1 + 1;
		GLuint indexCount = 3 * ::slices;
		circleData->vertexData.resize(vertexCount);
		circleData->indices.resize(indexCount);
		GLuint vertexIndex = 0, indexIndex = 0;
		GLfloat per_theta =  glm::two_pi<GLfloat>()/ ::slices;
		GLfloat theta = 0.0f;
		//圆心
		circleData->vertexData[vertexIndex++] = {
			vec3(0.0f, 0.0f, 0.0f),
			vec3(1.0f, 0.0f, 0.0f),
			vec2(0.5f, 0.5f)
		};
		for (int i = 0; i <= ::slices; i++)
		{
			theta = i * per_theta;
			circleData->vertexData[vertexIndex++] = {
				vec3(0.0f, radius * sinf(theta), -radius * cosf(theta)),
				vec3(0.0f, sinf(theta), -cosf(theta)),
				vec2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f)
			};
		}
		for (GLuint i = 1; i <= ::slices; ++i)
		{
			circleData->indices[indexIndex++] = i;
			circleData->indices[indexIndex++] = i % (::slices + 1) + 1;
			circleData->indices[indexIndex++] = 0;
		}

	}
	return circleData;
}

shared_ptr<Mesh> VertexFactory::getCylinderNoCapData()
{
	if (cylinderNoCapData->vertexData.empty())
	{
		GLuint vertexCount = 2 * (::slices + 1);
		GLuint indexCount = 6 * ::slices;
		cylinderNoCapData->vertexData.resize(vertexCount);
		cylinderNoCapData->indices.resize(indexCount);
		float height = 1.0f;
		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = glm::two_pi<GLfloat>() / ::slices;
		GLuint vertexIndex = 0, indexIndex = 0;
		// 侧面顶端点
		for (GLuint i = 0; i <= ::slices; ++i)
		{
			theta = i * per_theta;
			cylinderNoCapData->vertexData[vertexIndex++] = {
				vec3(h2, radius * sinf(theta), -radius * cosf(theta)),
				vec3(0.0f, sinf(theta), -cosf(theta)),
				vec2(0.0f, 1.0f - theta / glm::two_pi<GLfloat>()) };
		}

		// 侧面底端点
		for (GLuint i = 0; i <= ::slices; ++i)
		{
			theta = i * per_theta;
			cylinderNoCapData->vertexData[vertexIndex++] = {
				vec3(-h2, radius * sinf(theta), -radius * cosf(theta)),
				vec3(0.0f, sinf(theta), -cosf(theta)),
				vec2(1.0f, 1.0f - theta / glm::two_pi<GLfloat>()) };
		}

		// 索引

		for (GLuint i = 0; i < ::slices; ++i)
		{
			cylinderNoCapData->indices[indexIndex++] = (::slices + 1) + i + 1;
			cylinderNoCapData->indices[indexIndex++] = i + 1;
			cylinderNoCapData->indices[indexIndex++] = i;

			cylinderNoCapData->indices[indexIndex++] = i;
			cylinderNoCapData->indices[indexIndex++] = (::slices + 1) + i;
			cylinderNoCapData->indices[indexIndex++] = (::slices + 1) + i + 1;
		}

	}
	return cylinderNoCapData;
}

shared_ptr<Mesh> VertexFactory::getCylinderData()
{
	if (cylinderData->vertexData.empty())
	{
		auto p_cnc = VertexFactory::getCylinderNoCapData();
		auto p_c = VertexFactory::getCircleData();
		GLuint vertexCount = p_cnc->vertexData.size() +
			p_c->vertexData.size() * 2;
		GLuint indexCount = p_cnc->indices.size() +
			p_c->indices.size() * 2;


		cylinderData->vertexData.resize(vertexCount);
		cylinderData->indices.resize(indexCount);
		GLuint vertexIndex = 0, indexIndex = 0;
		short offset_1 = 0, offset_2 = 0;// 因为是拼接三个模型所以需要两个顶点偏移量
		float height = 1.0f;
		float h2 = height / 2;
		for (auto data : p_cnc->vertexData)
			cylinderData->vertexData[vertexIndex++] = data;

		offset_1 = vertexIndex;//更新偏移量1
		 // 右面 (+X)面
		for (auto data : p_c->vertexData)
			cylinderData->vertexData[vertexIndex++] = {
			vec3(h2, data.pos.y, data.pos.z),
			data.normal,
			data.tex
		};

		offset_2 = vertexIndex;// 更新偏移量2
		// 左面 (-X)面
		for (auto data : p_c->vertexData)
			cylinderData->vertexData[vertexIndex++] = {
			vec3(-h2, data.pos.y, -data.pos.z),
			vec3(-data.normal.x, data.normal.y, data.normal.z),
			data.tex
		};

		for (auto index : p_cnc->indices)
			cylinderData->indices[indexIndex++] = index;

		for (auto index : p_c->indices)
			cylinderData->indices[indexIndex++] = index + offset_1;

		for (auto index : p_c->indices)
			cylinderData->indices[indexIndex++] = index + offset_2;
	}
	return cylinderData;
}

shared_ptr<Mesh> VertexFactory::getSphereData()
{
	if (sphereData->vertexData.empty())
	{
		GLuint vertexCount = 2 + (levels - 1) * (slices + 1);
		GLuint indexCount = 6 * (levels - 1) * slices;
		sphereData->vertexData.resize(vertexCount);
		sphereData->indices.resize(indexCount);

		GLuint vertexIndex = 0, indexIndex = 0;

		float phi = 0.0f, theta = 0.0f;
		float per_phi = glm::pi<GLfloat>() / levels;
		float per_theta = glm::two_pi<GLfloat>() / slices;
		float x, y, z;

		// 顶点
		sphereData->vertexData[vertexIndex++] = { vec3(0.0f, radius, 0.0f), vec3(0.0f, 1.0f, 0.0f),  vec2(0.0f, 0.0f) };

		for (GLuint i = 1; i < levels; ++i)
		{
			phi = per_phi * i;
			for (GLuint j = 0; j <= slices; ++j)
			{
				theta = per_theta * j;
				x = radius * sinf(phi) * cosf(theta);
				y = radius * cosf(phi);
				z = radius * sinf(phi) * sinf(theta);

				vec3 pos = vec3(x, y, -z);
				vec3 normal = glm::normalize(pos);
				sphereData->vertexData[vertexIndex++] = { pos, normal, vec2(theta / glm::two_pi<GLfloat>(), phi / glm::pi<GLfloat>()) };
			}
		}

		// 底端点
		sphereData->vertexData[vertexIndex++] = { vec3(0.0f, -radius, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f) };


		// 顶端索引
		if (levels > 1)
		{
			for (GLuint j = 1; j <= slices; ++j)
			{
				sphereData->indices[indexIndex++] = j;
				sphereData->indices[indexIndex++] = j % (slices + 1) + 1;
				sphereData->indices[indexIndex++] = 0;
			}
		}

		// 中间几层的索引
		for (GLuint i = 1; i < levels - 1; ++i)
		{
			for (GLuint j = 1; j <= slices; ++j)
			{
				sphereData->indices[indexIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
				sphereData->indices[indexIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
				sphereData->indices[indexIndex++] = (i - 1) * (slices + 1) + j;

				sphereData->indices[indexIndex++] = (i - 1) * (slices + 1) + j;
				sphereData->indices[indexIndex++] = i * (slices + 1) + j;
				sphereData->indices[indexIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
			}
		}

		// 底端索引
		if (levels > 1)
		{
			for (GLuint j = 1; j <= slices; ++j)
			{
				sphereData->indices[indexIndex++] = (levels - 1) * (slices + 1) + 1;
				sphereData->indices[indexIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
				sphereData->indices[indexIndex++] = (levels - 2) * (slices + 1) + j;
			}
		}
	}

	return sphereData;
}

shared_ptr<Mesh> VertexFactory::getPlaneData()
{
	if (planeData->vertexData.empty())
	{
		GLuint vertexCount = 4;
		GLuint indexCount = 6;
		planeData->vertexData.resize(vertexCount);
		planeData->indices.resize(indexCount);
		float w = 0.5f;
		float d = 0.5f;
		planeData->vertexData[0] = { vec3(w, 0.0f, d), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) };
		planeData->vertexData[1] = { vec3(w, 0.0f, -d), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f) };
		planeData->vertexData[2] = { vec3(-w, 0.0f, -d), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f) };
		planeData->vertexData[3] = { vec3(-w, 0.0f, d), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f) };


		planeData->indices = {
			3, 1, 0,
			3, 2, 1
		};
	}
	return planeData;
}

shared_ptr<Mesh> VertexFactory::getTestPlaneData()
{
	if (testPlaneData->vertexData.empty())
	{
		GLuint vertexCount = 4;
		GLuint indexCount = 6;
		testPlaneData->vertexData.resize(vertexCount);
		testPlaneData->indices.resize(indexCount);
		float w = 1.0f;
		float d = 1.0f;
		testPlaneData->vertexData[0] = { vec3(-d, w, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f) };
		testPlaneData->vertexData[1] = { vec3(d, w, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f) };
		testPlaneData->vertexData[2] = { vec3(d, -w, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f) };
		testPlaneData->vertexData[3] = { vec3(-d, -w, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f) };


		testPlaneData->indices = {
			0, 1, 3,
			1, 2, 3
		};
	}
	return testPlaneData;
}

// 地板网格
shared_ptr<Mesh> VertexFactory::getGroundData()
{
	if (goundData->vertexData.empty())
	{
		int side = 20;	// 地板方块的数量
		GLuint vertexCount = 4 * 20 * 20;	
		GLuint indexCount = 6 * 20 * 20;
		goundData->vertexData.resize(vertexCount);
		goundData->indices.resize(indexCount);
		short vertexIndex = 0, indexIndex = 0;


		// 纹理坐标
		vec2 texC[4] = {
			vec2(1.0f, 1.0f),
			vec2(1.0f, 0.0f),
			vec2(0.0f, 0.0f),
			vec2(0.0f, 1.0f)
		};
		// 法线
		vec3 normal(0.0f, 1.0f, 0.0f);
		float w = 1.0f;	// 宽度
		float d = 1.0f;	// 高度
		float w2 = w / 2;
		float d2 = d / 2;
		// 地板左上角点的坐标
		float originX = (-side * w) / 2.0f;
		float originZ = (side * d) / 2.0f;
		// 填充顶点数据
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				float x = originX + i * w;
				float z = originZ - j * d;
				goundData->vertexData[vertexIndex++] = { vec3(w2 + x, 0.0f, d2 - z), normal, texC[0] };
				goundData->vertexData[vertexIndex++] = { vec3(w2 + x, 0.0f, -d2 - z), normal, texC[1] };
				goundData->vertexData[vertexIndex++] = { vec3(-w2 + x, 0.0f, -d2 - z), normal, texC[2] };
				goundData->vertexData[vertexIndex++] = { vec3(-w2 + x, 0.0f, d2 - z), normal, texC[3] };
			}
		}

		// 填充索引
		short indices[6] = {
			0, 1, 3,
			1, 2, 3
		};
		for (int i = 0; i < side * side; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				goundData->indices[indexIndex++] = indices[j] + i * 4;
			}
		}
	}
	return goundData;
}
