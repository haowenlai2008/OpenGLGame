#pragma once
#include "func.h"
#include <map>
using std::pair;
using std::map;
class Material
{
public:
	enum class TextureType
	{
		ShadowMap,
		Texture2D = GL_TEXTURE_2D,
		TextureCubMap = GL_TEXTURE_CUBE_MAP,
	};
	class TextureStructure
	{
	public:
		TextureStructure(const string& path, Material::TextureType textureType) : m_path(path), m_textureType(textureType), m_textureID(0)
		{

		}
		TextureStructure(string&& path, Material::TextureType textureType) : m_path(path), m_textureType(textureType), m_textureID(0)
		{
			
		}
		string m_path;					// ��Դ·��
		TextureType m_textureType;		// ��������
		GLuint m_textureID;				// ������ID
	};
	Material();
	Material(const vec3& specular, float shininess);
	Material(vec3&& specular, float shininess);
	LL_SYNTHESIZE(vec3, m_specular, Specular);
	LL_SYNTHESIZE(float, m_shininess, Shininess);
	string m_shaderName;
	weak_ptr<Shader> m_Shader;
	map<int, TextureStructure> textureList;		// ��¼ÿ��Textureλ�ö�Ӧ����������
	// ����uniform
	map<string, bool> uniformBool;
	map<string, int> uniformInt;
	map<string, float> uniformFloat;
	map<string, vec2> uniformVec2;
	map<string, vec3> uniformVec3;
	map<string, vec4> uniformVec4;
	map<string, mat2> uniformMat2;
	map<string, mat3> uniformMat3;
	map<string, mat4> uniformMat4;
};

