#include "MaterialManager.h"

bool MaterialManager::init()
{
	shaderTypeMap = {
	{MaterialType::PBRCube, "PBRCube"},
	{MaterialType::WithColor, "WithColor"},
	{MaterialType::WithColorAndLight, "WithColorAndLight"},
	{MaterialType::WithTex, "WithTex"},
	{MaterialType::PBR, "PBR"},
	{MaterialType::SimpleDepth, "simpleDepth"},
	{MaterialType::SkyBox, "SkyBox"},
	{MaterialType::SkyBoxHDR, "SkyBoxHDR"},
	{MaterialType::EquirectangularToCubemap, "EquirectangularToCubemap"},
	{MaterialType::ModelPBR, "1.model_loading"},
	};


	systemMaterial = {
		{MaterialType::WithColor,{
			{"mColor", vec3(1.0)},
		}},
		{MaterialType::WithColorAndLight, {}},
		{MaterialType::WithTex, {}},
		{MaterialType::PBR, {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{MaterialType::PBRCube, {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", Texture(TextureType::TextureCubMap, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
		{MaterialType::SimpleDepth, {}},
		{MaterialType::SkyBox, {
			{"material.diffuse", Texture("skybox3", TextureType::TextureCubMap, 0)},
			{"environmentMap", Texture(TextureType::TextureEnv, 1)},
		}},
		{MaterialType::SkyBoxHDR, {
			{"equirectangularMap", Texture("Alexs_Apartment/Alexs_Apt_2k.hdr", TextureType::TextureHDR, 0)},
		}},
		{MaterialType::EquirectangularToCubemap, {
			{"equirectangularMap", Texture("Alexs_Apartment/Alexs_Apt_2k.hdr", TextureType::TextureHDR, 0)},
		}},
		{MaterialType::ModelPBR, {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", Texture(TextureType::Texture2D, 0)},
			{"shadowMap", Texture(TextureType::ShadowMap, 1)},
		}},
	};
    return true;
}

Material& MaterialManager::getSystemMaterial(MaterialType materialType)
{
	auto& mat = systemMaterial[materialType];
	if (mat.m_Shader.expired())
	{
		mat.m_Shader = Shader::getShader(shaderTypeMap[materialType]);
	}
	return mat;
}

//Material& MaterialManager::createMaterial(const string& matKey)
//{
//	// TODO: 在此处插入 return 语句
//}
//
//Material& MaterialManager::createMaterial(const string& matKey, MaterialType materialType)
//{
//	return Material();
//}
