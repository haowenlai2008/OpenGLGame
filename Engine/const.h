#pragma once
#include <vector>
#include <string>
#include <glm/vec3.hpp>
using std::vector;
using std::string;
using glm::vec3;
#define ERROR_TEX_ID -1
#define TEXTURE_PATH (std::string("Resources/Texture/"))	//纹理的路径
#define SHADER_PATH (std::string("Resources/Shader/"))		//Shader的路径
#define MODEL_PATH (std::string("Resources/Model/"))			//模型的路径
#define DOT_MAT_PATH (std::string("Resources/DotMatrix/"))	//点阵的路径
#define FILTER_PATH (std::string("Resources/Shader/Filter/"))	//滤镜的路径
#define FILTER_VS (std::string("Resources/Shader/Filter/filterBase.vs"))	//滤镜的顶点着色器
#define SKY_BOX (std::string("sor_cwd"))

namespace Const
{
	static vector<string> facesName = 
	{
		"/right.jpg",
		"/left.jpg",
		"/top.jpg",
		"/bottom.jpg",
		"/front.jpg",
		"/back.jpg"
	};

	class EntityColor
	{
	public:
		static vec3 Red;
		static vec3 Orange;
		static vec3 Yellow;
		static vec3 Green;
		static vec3 Cyan;
		static vec3 Blue;
		static vec3 Purple;
		static vec3 Grey;
		static vec3 Pink;
		static vec3 Black;
	};
}
