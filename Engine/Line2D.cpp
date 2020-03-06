#include "Line2D.h"
#include "allShaderComponent.h"

void Line2D::addPoint(glm::vec2 point)
{
	points.emplace_back(point.x);
	points.emplace_back(point.y);
}

void Line2D::clear()
{
	points.clear();
}

void Line2D::setColor(glm::vec3 color)
{
	//auto com = getComponent(ComponentTypeII::Shader2D_Line);
	//if (com != nullptr)
	//{
	//	static_cast<Shader2D_Line*>(com)->setColor(color);
	//}
}

bool Line2D::init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);// 绑定顶点数组对象
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//绑定顶点缓冲区
	//setComponent(new Shader2D_Line());
	return true;
}

void Line2D::draw()
{
	glBindVertexArray(m_VAO);
	glLineWidth(5);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.begin()._Ptr, GL_STREAM_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * points.size(), points.begin()._Ptr);
	glGetError();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glGetError();
	Entity::draw();
	glDrawArrays(GL_LINE_STRIP, 0, points.size() / 2);
	glGetError();
	glBindVertexArray(0);
}

void Line2D::update(float delta)
{

}
