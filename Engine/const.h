#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
#define TEXTURE_PATH (std::string("Resources/Texture/"))	//�����·��
#define SHADER_PATH (std::string("Resources/Shader/"))		//Shader��·��
#define MODEL_PATH (std::string("Resources/Model/"))			//ģ�͵�·��
#define DOT_MAT_PATH (std::string("Resources/DotMatrix/"))	//�����·��
#define FILTER_PATH (std::string("Resources/Shader/Filter/"))	//�˾���·��
#define FILTER_VS (std::string("Resources/Shader/Filter/filterBase.vs"))	//�˾��Ķ�����ɫ��
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
}
