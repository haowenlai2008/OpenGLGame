#pragma once
#include "func.h"
#include <unordered_map>
#include <list>
#include "Shader.h"

#define ERROR_TEX_ID -1
using std::pair;
using std::unordered_map;
using std::list;
using std::weak_ptr;


// 预设材质类型
enum class MaterialType
{
	WithColor,
	WithColorAndLight,
	WithTex,
	PBR,
	PBRCube, //
	SimpleDepth,
	SkyBox,
	SkyBoxHDR,
	EquirectangularToCubemap,
};

// Uniform数据类型
enum class UniformType
{
	Bool,
	Int,
	Float,
	Vec2,
	Vec3,
	Vec4,
	Mat2,
	Mat3,
	Mat4,
	Tex,
};

// 纹理类型
enum class TextureType
{
	ShadowMap,
	Texture2D,
	TextureHDR,
	TextureEnv,
	TextureCubMap,
};

// 纹理结构体
class TextureStructure
{
public:
	TextureStructure() : m_textureType(TextureType::Texture2D), m_location(-1), m_path(""),  m_textureID(ERROR_TEX_ID) {}
	TextureStructure(TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(""), m_textureID(ERROR_TEX_ID) {}
	TextureStructure(const string& path, TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(path), m_textureID(ERROR_TEX_ID){}
	TextureStructure(string&& path, TextureType textureType, GLubyte location) : m_textureType(textureType), m_location(location), m_path(path), m_textureID(ERROR_TEX_ID){}
	~TextureStructure() {}
	TextureType m_textureType;		// 纹理类型
	GLubyte m_location;				// 纹理位置
	string m_path;					// 资源路径
	GLuint m_textureID;				// 纹理缓存ID
};

union UniformUnion
{
	bool boolData;
	int intData;
	float floatData;
	vec2 vec2Data;
	vec3 vec3Data;
	vec4 vec4Data;
	mat2 mat2Data;
	mat3 mat3Data;
	mat4 mat4Data;
};
class UniformValue
{
public:
	UniformUnion data;
	TextureStructure texData;
	UniformType m_type;

	UniformValue(bool value) { data.boolData = value; m_type = UniformType::Bool; };
	UniformValue(int value) { data.intData = value; m_type = UniformType::Int; };
	UniformValue(float value) { data.floatData = value; m_type = UniformType::Float; };
	UniformValue(const vec2& value) { data.vec2Data = value; m_type = UniformType::Vec2; };
	UniformValue(vec2&& value) { data.vec2Data = value; m_type = UniformType::Vec2; };
	UniformValue(const vec3& value) { data.vec3Data = value; m_type = UniformType::Vec3; };
	UniformValue(vec3&& value) { data.vec3Data = value; m_type = UniformType::Vec3; };
	UniformValue(const vec4& value) { data.vec4Data = value; m_type = UniformType::Vec4; };
	UniformValue(vec4&& value) { data.vec4Data = value; m_type = UniformType::Vec4; };
	UniformValue(const mat2& value) { data.mat2Data = value; m_type = UniformType::Mat2; };
	UniformValue(mat2&& value) { data.mat2Data = value; m_type = UniformType::Mat2; };
	UniformValue(const mat3& value) { data.mat3Data = value; m_type = UniformType::Mat3; };
	UniformValue(mat3&& value) { data.mat3Data = value; m_type = UniformType::Mat3; };
	UniformValue(const mat4& value) { data.mat4Data = value; m_type = UniformType::Mat4; };
	UniformValue(mat4&& value) { data.mat4Data = value; m_type = UniformType::Mat4; };
	UniformValue(const TextureStructure& value) { texData = value; m_type = UniformType::Mat4; };
	UniformValue(TextureStructure&& value) { texData = value; m_type = UniformType::Tex; };
};

class Material
{
public:

	Material();
	Material(MaterialType entityType);
	Material(std::initializer_list<pair<string, UniformValue>> uniformList);
	LL_SYNTHESIZE(GLuint, m_state_cull, Cull)
	string m_shaderName;
	weak_ptr<Shader> m_Shader;

	bool castShadow;
	bool requireEnvironmentMap;
	// uniform
	unordered_map<string, bool> uniformBool;
	unordered_map<string, int> uniformInt;
	unordered_map<string, float> uniformFloat;
	unordered_map<string, vec2> uniformVec2;
	unordered_map<string, vec3> uniformVec3;
	unordered_map<string, vec4> uniformVec4;
	unordered_map<string, mat2> uniformMat2;
	unordered_map<string, mat3> uniformMat3;
	unordered_map<string, mat4> uniformMat4;
	// 记录每个Texture位置对应的纹理类型
	unordered_map<string, TextureStructure> uniformTex;
	// 记录特殊纹理
	unordered_map<TextureType, bool> textureRequireState;
	// DC前调用，设置所有Uniform
	void bindUniform();
	// uniform工具函数
	void setBool(const string& name, bool value);
	void setInt(const string& name, int value);
	void setFloat(const string& name, float value);
	void setVec2(const string& name, const vec2& value);
	void setVec2(const string& name, float x, float y);
	void setVec3(const string& name, const vec3& value);
	void setVec3(const string& name, float x, float y, float z);
	void setVec4(const string& name, const vec4& value);
	void setVec4(const string& name, float x, float y, float z, float w);
	void setMat2(const string& name, const glm::mat2& mat);
	void setMat3(const string& name, const glm::mat3& mat);
	void setMat4(const string& name, const glm::mat4& mat);

	void setTexture(const string& name, const string& path, TextureType textureType);
	void setTexture(const string& name, const string& path, GLubyte location, TextureType textureType);
	void setTextureLocation(const string& name, GLubyte location);
	void setTexturePath(const string& name, const string& path);
	void setTextureCacheID(const string& name, GLuint cacheID);

	bool hasTexture(const string& name);
	static Material& getSystemMaterial(MaterialType materialType);

private:
	// 系统自带材质，只能通过getSystemMaterial获取
	static vector<MaterialType> specialTexture;
	static unordered_map<MaterialType, std::string> shaderTypeMap;
	static unordered_map<MaterialType, Material> systemMaterial;
};

