#pragma once

// Ԥ���������
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

// Uniform��������
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

// ��������
enum class TextureType
{
	ShadowMap,
	Texture2D,
	TextureHDR,
	TextureEnv,
	TextureCubMap,
};