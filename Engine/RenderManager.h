#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "Singleton.h"
#include "func.h"
using std::list;
using std::map;
using std::string;
using std::vector;
class Node;
class Shader;
class Camera;
enum class RenderMode
{
	TestDepthMap,
	Normal,
};
class RenderManager : public Singleton<RenderManager>
{
public:
	friend class Singleton<RenderManager>;
	static vector<float> quadVertices;
	static unsigned int getTexture(string& path);
	static unsigned int getTextureByAbsolutePath(string& path);
	static unsigned int getHDRTexture(string& path);
	static unsigned int getCubeTexture(string& path);
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
	void renderEntity(Node* p);
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
	list<Node*> drawObjects;		// 需要渲染的物体集合，每帧清除
	static map<string, int> textures;
	void filterInit();
};
