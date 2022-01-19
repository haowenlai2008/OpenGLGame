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
			{"material.diffuse", TextureStructure(TextureType::Texture2D, 0)},
			{"shadowMap", TextureStructure(TextureType::ShadowMap, 1)},
		}},
		{MaterialType::PBRCube, {
			{"viewPos", vec3(0.0f)},
			{"light.position", vec3(0.0f)},
			{"light.ambient", vec3(0.2f, 0.2f, 0.2f)},
			{"light.diffuse", vec3(0.5f, 0.5f, 0.5f)},
			{"light.specular", vec3(1.0f, 1.0f, 1.0f)},
			{"material.specular", vec3(0.5f, 0.5f, 0.5f)},
			{"material.shininess", 64.0f},
			{"material.diffuse", TextureStructure(TextureType::TextureCubMap, 0)},
			{"shadowMap", TextureStructure(TextureType::ShadowMap, 1)},
		}},
		{MaterialType::SimpleDepth, {}},
		{MaterialType::SkyBox, {
			{"material.diffuse", TextureStructure("skybox3", TextureType::TextureCubMap, 0)},
			{"environmentMap", TextureStructure(TextureType::TextureEnv, 1)},
		}},
		{MaterialType::SkyBoxHDR, {
			{"equirectangularMap", TextureStructure("Alexs_Apartment/Alexs_Apt_2k.hdr", TextureType::TextureHDR, 0)},
		}},
		{MaterialType::EquirectangularToCubemap, {
			{"equirectangularMap", TextureStructure("Alexs_Apartment/Alexs_Apt_2k.hdr", TextureType::TextureHDR, 0)},
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
