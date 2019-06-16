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
	unsigned int framebuffer;			//֡����
	unsigned int textureColorbuffer;	//��ɫ����
	unsigned int rbo;					//��Ⱦ�������
	unsigned int quadVAO, quadVBO;		//֡����Ĵ��ڵĶ����������Ͷ��㻺�����
	
	static RenderManager* renderManager;
	static map<string, int> textures;
	
	RenderManager();
	void filterInit();
	
};
