#pragma once
#include <iostream>
#include <glfw3.h>
#include <glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <stb_image.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "const.h"
using glm::vec3;
using glm::vec2;
using glm::mat4;
using std::vector;
using std::string;


#define LL_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType& var){ varName = var; }\
public: virtual void set##funName(varType&& var){ varName = var; }

#define LL_SYNTHESIZE_READ(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) { return varName; }\
protected: virtual void set##funName(varType var){ varName = var; }\
public:

#define LL_STATIC_SYNTHESIZE(varType, varName, funName)\
public: static varType varName;\
public: static varType get##funName(void) { return varName; }\
public: static void set##funName(varType var){ varName = var; }

unsigned int loadCubemap(vector<std::string> faces);
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}
#define DEBUG_VEC3(VEC3) std::cout << std::string(#VEC3) + " = " << "(" << VEC3.x <<"," << VEC3.y <<"," << VEC3.z <<")" << std::endl;
//加载纹理
template <typename S1 = std::string>
void LoadTexture(unsigned int &texture, S1&& pic)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载并生成纹理
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load((TEXTURE_PATH + std::forward<std::string>(pic)).c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		//位深度为24，3个通道(jpg
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//位深度为32，4个通道(png
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	data = nullptr;
}

