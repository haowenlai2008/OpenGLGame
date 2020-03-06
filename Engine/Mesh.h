#pragma once
#include "func.h"
#include <vector>
using std::vector;
using std::shared_ptr;
struct MeshData
{
	vec3 pos;
	vec3 normal;
	vec2 tex;
};

class Mesh
{
public:
	Mesh() = default;
	Mesh(const Mesh&) = default;
	Mesh& operator=(const Mesh&) = default;
	Mesh(Mesh&&) = default;
	Mesh& operator=(Mesh&&) = default;
	vector<MeshData> vertexData;
	vector<GLuint> indices;
};
