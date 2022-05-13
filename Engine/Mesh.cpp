#include "Mesh.h"

void Mesh::setupMesh()
{
	if (VAO != -1)
	{
		glDeleteVertexArrays(1, &VAO);
	}

	if (VBO != -1)
	{
		glDeleteBuffers(1, &VBO);
	}
	if (EBO != -1)
	{
		glDeleteBuffers(1, &EBO);
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);// �󶨶����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//�󶨶��㻺����
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.begin()._Ptr, GL_STATIC_DRAW);
	//����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glEnableVertexAttribArray(0);
	//����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//����������
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.begin()._Ptr, GL_STATIC_DRAW);
	glBindVertexArray(0);
}