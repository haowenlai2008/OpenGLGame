#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "Shader.h"
using std::list;
using std::map;
using std::string;
using std::vector;
class Node;
class RenderManager
{
public:
	static vector<float> quadVertices;
	static RenderManager* getInstance();
	static unsigned int getTexture(string& path);
	void init();
	
	void update(Node* node);
	void bindFrameBuffer();
	void filterUse();
	Shader screenShader;
	~RenderManager();
private:
	unsigned int framebuffer;			//帧缓冲
	unsigned int textureColorbuffer;	//颜色缓冲
	unsigned int rbo;					//渲染缓冲对象
	unsigned int quadVAO, quadVBO;		//帧缓冲的窗口的顶点数组对象和顶点缓冲对象
	
	static RenderManager* renderManager;
	static map<string, int> textures;
	
	RenderManager();
	void filterInit();
	
};
