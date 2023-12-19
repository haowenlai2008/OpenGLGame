#include "Material.h"
#include "RenderManager.h"
#include <unordered_map>

Material::Material() : castShadow(false), requireEnvironmentMap(false)
{
}


Material::Material(std::initializer_list<pair<string, UniformValue>> uniformList) : 
	castShadow(false),
	requireEnvironmentMap(false)
{
	for (auto& [uniformName, uniformValue] : uniformList)
	{
		switch (uniformValue.m_type)
		{
		case UniformType::Bool:
			uniformBool.insert({ uniformName, std::get<bool>(uniformValue.data) });
			break;
		case UniformType::Int:
			uniformInt.insert({ uniformName, std::get<int>(uniformValue.data) });
			break;
		case UniformType::Float:
			uniformFloat.insert({ uniformName, std::get<float>(uniformValue.data) });
			break;
		case UniformType::Vec2:
			uniformVec2.insert({ uniformName, std::get<vec2>(uniformValue.data) });
			break;
		case UniformType::Vec3:
			uniformVec3.insert({ uniformName, std::get<vec3>(uniformValue.data) });
			break;
		case UniformType::Vec4:
			uniformVec4.insert({ uniformName, std::get<vec4>(uniformValue.data) });
			break;
		case UniformType::Mat2:
			uniformMat2.insert({ uniformName, std::get<mat2>(uniformValue.data) });
			break;
		case UniformType::Mat3:
			uniformMat3.insert({ uniformName, std::get<mat3>(uniformValue.data) });
			break;
		case UniformType::Mat4:
			uniformMat4.insert({ uniformName, std::get<mat4>(uniformValue.data) });
			break;
		case UniformType::Tex:
			// 确定该材质为产生阴影的材质
			if (uniformValue.texData.m_textureType == TextureType::ShadowMap)
				castShadow = true;
			if (uniformValue.texData.m_textureType == TextureType::TextureEnv)
				requireEnvironmentMap = true;
			uniformTex.insert({ uniformName, uniformValue.texData});
			break;
		default:
			break;
		}
	}
}

void Material::bindUniform()
{
	if (m_Shader.expired())
		return;
	auto shader = m_Shader.lock();
	for (auto& pair : uniformBool)
		shader->setBool(pair.first, pair.second);
	for (auto& pair : uniformInt)
		shader->setInt(pair.first, pair.second);
	for (auto& pair : uniformFloat)
		shader->setFloat(pair.first, pair.second);
	for (auto& pair : uniformVec2)
		shader->setVec2(pair.first, pair.second);
	for (auto& pair : uniformVec3)
		shader->setVec3(pair.first, pair.second);
	for (auto& pair : uniformVec4)
		shader->setVec4(pair.first, pair.second);
	for (auto& pair : uniformMat2)
		shader->setMat2(pair.first, pair.second);
	for (auto& pair : uniformMat3)
		shader->setMat3(pair.first, pair.second);
	for (auto& pair : uniformMat4)
		shader->setMat4(pair.first, pair.second);

	// 绑定纹理
	for (auto& pair : uniformTex)
	{
		auto& texInfo = pair.second;
		string srcPath = texInfo.m_path;
		GLuint texType = GL_TEXTURE_2D;
		GLuint textureID = ERROR_TEX_ID;
		TextureType textureType = texInfo.m_textureType;

		// 读文件的纹理
		if (texInfo.m_textureID == ERROR_TEX_ID && texInfo.m_path != "") // 有路径但是没加载的话加载一次
		{
			switch (textureType)
			{
			case TextureType::TextureHDR:
				textureID = ResourceTools::getHDRTexture(srcPath);
				break;
			case TextureType::TextureCubMap:
				textureID = ResourceTools::getCubeTexture(srcPath);
				texType = GL_TEXTURE_CUBE_MAP;
				break;
			default:
				textureID = ResourceTools::getTexture(srcPath);
				break;
			}
		}
		else
			textureID = texInfo.m_textureID;


		// 特殊纹理
		switch (textureType)
		{
		case TextureType::TextureEnv:
			textureID = RenderManager::globleTexture.environmentMapIBL;
			texType = GL_TEXTURE_CUBE_MAP;
			break;
		case TextureType::ShadowMap:
			textureID = RenderManager::globleTexture.shadowMapTexture;
			texType = GL_TEXTURE_2D;
			break;
		case TextureType::TextureCubMap:
			texType = GL_TEXTURE_CUBE_MAP;
			break;
		case TextureType::TexturePrefilter:
			textureID = RenderManager::globleTexture.prefilterMapIBL;
			texType = GL_TEXTURE_CUBE_MAP;
			break;
		case TextureType::TextureBrdfLUT:
			textureID = RenderManager::globleTexture.brdfLUT;
			texType = GL_TEXTURE_2D;
			break;
		case TextureType::GBufferPos:
			textureID = RenderManager::globleTexture.gBuffer_Position;
			texType = GL_TEXTURE_2D;
			break;
		case TextureType::GBufferNormal:
			textureID = RenderManager::globleTexture.gBuffer_Normal;
			texType = GL_TEXTURE_2D;
			break;
		case TextureType::GBufferAlbedo:
			textureID = RenderManager::globleTexture.gBuffer_Albedo;
			texType = GL_TEXTURE_2D;
			break;
		case TextureType::GBufferMetallicRoughness:
			textureID = RenderManager::globleTexture.gBuffer_MetallicRoughness;
			texType = GL_TEXTURE_2D;
			break;
		case TextureType::TextureIrradianceMap:
			textureID = RenderManager::globleTexture.irradianceMapIBL;
			texType = GL_TEXTURE_CUBE_MAP;
			break;
		default:
			break;
		}

		texInfo.m_textureID = textureID;

		if (texInfo.m_textureID == ERROR_TEX_ID)
			continue;
		shader->setInt(pair.first, texInfo.m_location);
		glActiveTexture(GL_TEXTURE0 + texInfo.m_location);
		glBindTexture(texType, texInfo.m_textureID);
	}
}

void Material::setBool(const string& name, bool value)
{
	uniformBool[name] = value;
}

void Material::setInt(const string& name, int value)
{
	uniformInt[name] = value;
}

void Material::setFloat(const string& name, float value)
{
	uniformFloat[name] = value;
}

void Material::setVec2(const string& name, const vec2& value)
{
	uniformVec2[name] = value;
}

void Material::setVec2(const string& name, float x, float y)
{
	uniformVec2[name] = vec2(x, y);
}

void Material::setVec3(const string& name, const vec3& value)
{
	uniformVec3[name] = value;
}

void Material::setVec3(const string& name, float x, float y, float z)
{
	uniformVec3[name] = vec3(x, y, z);
}

void Material::setVec4(const string& name, const vec4& value)
{
	uniformVec4[name] = value;
}

void Material::setVec4(const string& name, float x, float y, float z, float w)
{
	uniformVec4[name] = vec4(x, y, z, w);
}

void Material::setMat2(const string& name, const glm::mat2& mat)
{
	uniformMat2[name] = mat;
}

void Material::setMat3(const string& name, const glm::mat3& mat)
{
	uniformMat3[name] = mat;
	
}

void Material::setMat4(const string& name, const glm::mat4& mat)
{
	uniformMat4[name] = mat;
}

optional<float> Material::getFloat(const string& name)
{
	if (uniformFloat.count(name))
		return uniformFloat[name];
	return std::nullopt;
}

optional<vec2> Material::getVec2(const string& name)
{
	if (uniformVec2.count(name))
		return uniformVec2[name];
	return std::nullopt;
}

optional<vec3> Material::getVec3(const string& name)
{
	if (uniformVec3.count(name))
		return uniformVec3[name];
	return std::nullopt;
}

optional<vec4> Material::getVec4(const string& name)
{
	if (uniformVec4.count(name))
		return uniformVec4[name];
	return std::nullopt;
}

optional<mat2> Material::getMat2(const string& name)
{
	if (uniformMat2.count(name))
		return uniformMat2[name];
	return std::nullopt;
}

optional<mat3> Material::getMat3(const string& name)
{
	if (uniformMat3.count(name))
		return uniformMat3[name];
	return std::nullopt;
}

optional<mat4> Material::getMat4(const string& name)
{
	if (uniformMat4.count(name))
		return uniformMat4[name];
	return std::nullopt;
}

optional<Texture> Material::getTexture(const string& name)
{
	if (uniformTex.count(name))
		return uniformTex[name];
	return std::nullopt;
}

void Material::setTexture(const string& name, const string& path, TextureType textureType)
{
	if (uniformTex.count(name))
	{
		uniformTex[name].m_path = path;
		uniformTex[name].m_textureType = textureType;
	}
	else
	{
		uniformTex[name] = Texture(path, textureType, -1);
	}
}

void Material::setTexture(const string& name, const string& path, GLubyte location, TextureType textureType)
{
	uniformTex[name] = Texture(path, textureType, location);
}

void Material::setTexture(const string& name, Texture& texture, GLubyte location)
{
	auto curTex = Texture();
	curTex.m_location = location;
	curTex.m_path = texture.m_path;
	curTex.m_textureType = texture.m_textureType;
	curTex.m_type = texture.m_type;
	curTex.m_textureID = texture.m_textureID;
	uniformTex[name] = curTex;
}

void Material::setTextureLocation(const string& name, GLubyte location)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_location = location;
	}
	else
	{
		std::cout << "Texture " << name << " doesn't exist" << std::endl;
	}
}

void Material::setTexturePath(const string& name, const string& path)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_path = path;
	}
	else
	{
		std::cout << "Texture " << name << " doesn't exist" << std::endl;
	}
}

void Material::setTextureCacheID(const string& name, GLuint cacheID)
{
	if (uniformTex.find(name) != uniformTex.end())
	{
		uniformTex[name].m_textureID = cacheID;
	}
	else
	{
		std::cout << "Texture " << name << " doesn't exist" << std::endl;
	}
}

bool Material::hasTexture(const string& name)
{
	return uniformTex.find(name) != uniformTex.end();
}

