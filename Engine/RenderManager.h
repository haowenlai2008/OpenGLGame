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
	GLuint shadowMapTexture;
	GLuint environmentMapIBL;
	GLuint scenePassTexture;
	GLuint irradianceMapIBL;
	GLuint prefilterMapIBL;
	GLuint brdfLUT;
};

// 全局buffer
struct GlobleBufferStructure
{
	GLuint shadowMapBuffer;
	GLuint environmentBufferIBL;
	GLuint scenePassBuffer;
};

class RenderManager : public Singleton<RenderManager>
{
public:
	friend class Singleton<RenderManager>;
	list<Node*> drawObjects;		// 需要渲染的物体集合，每帧清除
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
