#pragma once
#include "func.h"
#include "Enum.h"
// ����ṹ��
class Texture
{
public:
	Texture() : m_textureType(TextureType::Texture2D), m_location(-1), m_path(""), m_textureID(ERROR_TEX_ID) {}
	Texture(TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(""), m_textureID(ERROR_TEX_ID) {}
	Texture(const string& path, TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(path), m_textureID(ERROR_TEX_ID) {}
	Texture(string&& path, TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(path), m_textureID(ERROR_TEX_ID) {}
	~Texture() {}
	TextureType m_textureType;		// ��������
	GLubyte m_location;				// ����λ��
	string m_path;					// ��Դ·��
	string m_type;					// ģ���е���������
	GLuint m_textureID;				// ������ID
};

struct Vertex
{
	vec3 pos;
	vec3 normal;
	vec2 tex;
};


