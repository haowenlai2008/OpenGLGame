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
#include "ResourceTools.h"
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat3;
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

//unsigned int loadCubemap(vector<std::string> faces);
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
#define DEBUG_BTVEC3(VEC3) std::cout << std::string(#VEC3) + " = " << "(" << VEC3.x() <<"," << VEC3.y() <<"," << VEC3.z() <<")" << std::endl;
