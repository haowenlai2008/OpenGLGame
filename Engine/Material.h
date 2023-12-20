#pragma once
#include "func.h"
#include <unordered_map>
#include <list>
#include <variant>
#include "Shader.h"
#include "Struct.h"
#include "Enum.h"
#include <optional>

using std::optional;
using std::pair;
using std::unordered_map;
using std::list;
using std::weak_ptr;
using namespace glm;

using UniformVariant = std::variant<bool, int, float, vec2, vec3, vec4, mat2, mat3, mat4>;

class UniformValue
{
public:
	UniformVariant data;
	Texture texData;
	UniformType m_type;

	UniformValue(bool value) :data(value) { m_type = UniformType::Bool; };
	UniformValue(int value) :data(value) { m_type = UniformType::Int; };
	UniformValue(float value) :data(value) { m_type = UniformType::Float; };
	UniformValue(const vec2& value) :data(value) { value; m_type = UniformType::Vec2; };
	UniformValue(vec2&& value) :data(value) { value; m_type = UniformType::Vec2; };
	UniformValue(const vec3& value) :data(value) { value; m_type = UniformType::Vec3; };
	UniformValue(vec3&& value) :data(value) { value; m_type = UniformType::Vec3; };
	UniformValue(const vec4& value) :data(value) { value; m_type = UniformType::Vec4; };
	UniformValue(vec4&& value) :data(value) { m_type = UniformType::Vec4; };
	UniformValue(const mat2& value) :data(value) { m_type = UniformType::Mat2; };
	UniformValue(mat2&& value) :data(value) { m_type = UniformType::Mat2; };
	UniformValue(const mat3& value) :data(value) { m_type = UniformType::Mat3; };
	UniformValue(mat3&& value) :data(value) { m_type = UniformType::Mat3; };
	UniformValue(const mat4& value) :data(value) { m_type = UniformType::Mat4; };
	UniformValue(mat4&& value) :data(value) { m_type = UniformType::Mat4; };
	UniformValue(const Texture& value) :data(0) { texData = value; m_type = UniformType::Mat4; };
	UniformValue(Texture&& value) :data(0) { texData = value; m_type = UniformType::Tex; };
};

class Material
{
public:

	Material();
	Material(std::initializer_list<pair<string, UniformValue>> uniformList);
	//LL_SYNTHESIZE(GLuint, m_state_cull, Cull)
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
	unordered_map<string, Texture> uniformTex;
	// 记录特殊纹理
	unordered_map<TextureType, bool> textureRequireState;
	// DC前调用，设置所有Uniform
	void bindUniform();
	// uniform工具函数
	void setBool(const string& name, bool value);
	void setInt(const string& name, int value);
	void setInt(const string& name, const optional<int>& valueOpt);
	void setFloat(const string& name, float value);
	void setFloat(const string& name, const optional<float>& valueOpt);
	void setVec2(const string& name, const vec2& value);
	void setVec2(const string& name, const optional<vec2>& valueOpt);
	void setVec2(const string& name, float x, float y);
	void setVec3(const string& name, const vec3& value);
	void setVec3(const string& name, const optional<vec3>& valueOpt);
	void setVec3(const string& name, float x, float y, float z);
	void setVec4(const string& name, const vec4& value);
	void setVec4(const string& name, const optional<vec4>& valueOpt);
	void setVec4(const string& name, float x, float y, float z, float w);
	void setMat2(const string& name, const mat2& mat);
	void setMat2(const string& name, const optional<mat2>& valueOpt);
	void setMat3(const string& name, const mat3& mat);
	void setMat3(const string& name, const optional<mat3>& valueOpt);
	void setMat4(const string& name, const mat4& mat);
	void setMat4(const string& name, const optional<mat4>& valueOpt);

	optional<float> getFloat(const string& name);
	optional<float> getFloat(const string& name);
	optional<vec2> getVec2(const string& name);
	optional<vec3> getVec3(const string& name);
	optional<vec4> getVec4(const string& name);
	optional<mat2> getMat2(const string& name);
	optional<mat3> getMat3(const string& name);
	optional<mat4> getMat4(const string& name);
	optional<Texture> getTexture(const string& name);

	void setTexture(const string& name, const string& path, TextureType textureType);
	void setTexture(const string& name, const string& path, GLubyte location, TextureType textureType);
	void setTexture(const string& name, Texture& texture, GLubyte location);
	void setTexture(const string& name, optional<Texture> texture, GLubyte location);
	void setTextureLocation(const string& name, GLubyte location);
	void setTexturePath(const string& name, const string& path);
	void setTextureCacheID(const string& name, GLuint cacheID);

	bool hasTexture(const string& name);
};

