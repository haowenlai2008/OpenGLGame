#pragma once

//// 预设材质类型
//enum class MaterialType
//{
//	WithColor,
//	WithColorAndLight,
//	WithTex,
//	WithTexAndLight,
//	PBR,
//	PBRCube, //
//	SimpleDepth,
//	SkyBox,
//	SkyBoxHDR,
//	EquirectangularToCubemap,
//	ModelPBR,
//};

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

// 渲染模式
enum class RenderMode
{
	TestDepthMap,
	Normal,
};