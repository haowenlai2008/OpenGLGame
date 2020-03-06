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
	LL_SYNTHESIZE(bool, m_IsShadow, IsShadow);	// �Ƿ�������Ⱦ��Ӱ
	~RenderManager();
private:
	unsigned int framebuffer;			//֡����
	unsigned int textureColorbuffer;	//��ɫ����
	unsigned int rbo;					//��Ⱦ�������
	unsigned int quadVAO, quadVBO;		//֡����Ĵ��ڵĶ����������Ͷ��㻺�����
	std::shared_ptr<Shader> screenShader;
	list<Node*> drawObjects;		// ��Ҫ��Ⱦ�����弯��
	static map<string, int> textures;
	void filterInit();
	
};
