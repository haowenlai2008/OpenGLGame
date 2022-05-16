#pragma once
#include "func.h"
#include "Enum.h"
// 纹理结构体
class Texture
{
public:
	Texture() : m_textureType(TextureType::Texture2D), m_location(-1), m_path(""), m_textureID(ERROR_TEX_ID) {}
	Texture(TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(""), m_textureID(ERROR_TEX_ID) {}
	Texture(const string& path, TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(path), m_textureID(ERROR_TEX_ID) {}
	Texture(string&& path, TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(path), m_textureID(ERROR_TEX_ID) {}
	~Texture() {}
	TextureType m_textureType;		// 纹理类型
	GLubyte m_location;				// 纹理位置
	string m_path;					// 资源路径
	string m_type;					// 模型中的纹理类型
	GLuint m_textureID;				// 纹理缓存ID
};

struct Vertex
{
	vec3 pos;
	vec3 normal;
	vec2 tex;
};


