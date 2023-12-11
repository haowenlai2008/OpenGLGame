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
	GLuint iblTexture;
	GLuint scenePassTexture;
};

// 全局buffer
struct GlobleBufferStructure
{
	GLuint shadowMapBuffer;
	GLuint iblBuffer;
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
	static GLuint getTexture(string& path);
	static GLuint getTextureByAbsolutePath(string& path);
	static GLuint getHDRTexture(string& path);
	static GLuint getCubeTexture(string& path);
	void init();
	void depthFBOInit();
	void equirectangularToCubemap();
	void update(Node* node);
	void draw();
	void bindFrameBuffer();
	void postProcess();
	void addDrawNode(Node* node);
	void shadowMapRenderBegin();
	void shadowMapRenderEnd();
	void renderScene();

	LL_SYNTHESIZE(bool, m_IsShadow, IsShadow);	// 是否正在渲染阴影
	LL_SYNTHESIZE(GLuint, m_CurrentFBO, CurrentFBO);	// 获得当前帧缓冲
	LL_SYNTHESIZE(RenderMode, m_Rendermode, RenderMode); // 设置当前渲染模式
	// 特殊贴图
	LL_SYNTHESIZE(GLuint, m_DepthMap, DepthMap);	// shadowmap
	LL_SYNTHESIZE(GLuint, m_EnvMap, EnvMap);		// 环境贴图
	std::shared_ptr<Shader> getSimpleDepthShader();
	~RenderManager();
private:

	GLuint framebuffer;			//帧缓冲
	GLuint textureColorbuffer;	//颜色缓冲
	GLuint rbo;					//渲染缓冲对象
	GLuint quadVAO, quadVBO;		//帧缓冲的窗口的顶点数组对象和顶点缓冲对象
	GLuint m_DepthFrameBuffer;		// 深度缓冲

	// 延迟渲染用
	GLuint gPosition;
	GLuint gNormal;
	GLuint gColorSpec;
	std::weak_ptr<Shader> m_SimpleDepthShader;
	std::weak_ptr<Shader> screenShader;

	static map<string, GLuint> textures;
	void filterInit();
};
