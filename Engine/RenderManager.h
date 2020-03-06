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
class RenderManager : public Singleton<RenderManager>
{
public:
	friend class Singleton<RenderManager>;
	static vector<float> quadVertices;
	static unsigned int getTexture(string& path);
	void init();
	void update(Node* node);
	void draw();
	void bindFrameBuffer();
	void filterUse();
	void addDrawNode(Node* node);
	LL_SYNTHESIZE(bool, m_IsShadow, IsShadow);	// 是否正在渲染阴影
	~RenderManager();
private:
	unsigned int framebuffer;			//帧缓冲
	unsigned int textureColorbuffer;	//颜色缓冲
	unsigned int rbo;					//渲染缓冲对象
	unsigned int quadVAO, quadVBO;		//帧缓冲的窗口的顶点数组对象和顶点缓冲对象
	std::shared_ptr<Shader> screenShader;
	list<Node*> drawObjects;		// 需要渲染的物体集合
	static map<string, int> textures;
	void filterInit();
	
};
