#pragma once
#include "opengl_game/core/func.h"
#include <vector>
#include "opengl_game/core/Struct.h"
using std::vector;
using std::shared_ptr;

class Mesh
{
public:
	Mesh() = default;
	Mesh(const Mesh&) = default;
	Mesh& operator=(const Mesh&) = default;
	Mesh(Mesh&&) = default;
	Mesh& operator=(Mesh&&) = default;
	vector<Vertex> vertexData;
	vector<GLuint> indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	unsigned int VAO;
	void setupMesh();
	void draw();
private:
	unsigned int VBO, EBO;
};
