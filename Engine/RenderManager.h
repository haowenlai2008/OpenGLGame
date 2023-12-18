#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "Singleton.h"
#include "func.h"
#include "Struct.h"
using std::list;
using std::map;
using std::string;
using std::vector;
class Node;
class Shader;
class Camera;
class RP_RenderPass;
// 全局纹理
struct GlobalTextureStructure
{
	GLuint shadowMapTexture = -1;
	GLuint environmentMapIBL = -1;		// 环境贴图
	GLuint scenePassTexture = -1;		// 前向渲染后的纹理
	GLuint irradianceMapIBL = -1;		// 环境贴图降采样后得到irradiance map
	GLuint prefilterMapIBL = -1;		// irradiance map生成的mipmap
	GLuint brdfLUT = -1;				// roughness-cos brdf的映射
	GLuint afterPossprocessTexture = -1;		// 后处理后的纹理
};

// 全局buffer
struct GlobleBufferStructure
{
	GLuint shadowMapBuffer = -1;
	GLuint environmentBufferIBL = -1;
	GLuint scenePassBuffer = -1;
	GLuint afterPossprocessBuffer = -1;
};

class RenderManager : public Singleton<RenderManager>
{
public:
	friend class Singleton<RenderManager>;
	list<Node*> drawObjects;		// 需要渲染的物体集合，每帧清除
	Node* skyBox;				// 天空盒单独抽出来
	list<std::shared_ptr<RP_RenderPass>> m_RenderPassList;	// 管线
	static GlobalTextureStructure globleTexture;	// 全局纹理
	static GlobleBufferStructure globalBuffer;		// 全局Buffer

	void init();
	void draw();
	void addDrawNode(Node* node);
private:
	// 延迟渲染用
	GLuint gPosition;
	GLuint gNormal;
	GLuint gColorSpec;

};
