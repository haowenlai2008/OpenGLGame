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
	void depthFBOInit();
	void update(Node* node);
	void draw();
	void bindFrameBuffer();
	void filterUse();
	void addDrawNode(Node* node);
	void shadowMapRenderBegin();
	void shadowMapRenderEnd();
	void renderScene();
	LL_SYNTHESIZE(bool, m_IsShadow, IsShadow);	// �Ƿ�������Ⱦ��Ӱ
	LL_SYNTHESIZE(GLuint, m_CurrentFBO, CurrentFBO);	// ��õ�ǰ֡����
	LL_SYNTHESIZE(GLuint, m_DepthMap, DepthMap);	// ��õ�ǰ֡����
	std::shared_ptr<Shader> getSimpleDepthShader();
	~RenderManager();
private:
	GLuint framebuffer;			//֡����
	GLuint textureColorbuffer;	//��ɫ����
	GLuint rbo;					//��Ⱦ�������
	GLuint quadVAO, quadVBO;		//֡����Ĵ��ڵĶ����������Ͷ��㻺�����
	GLuint m_DepthFrameBuffer;		// ��Ȼ���

	// �ӳ���Ⱦ��
	GLuint gPosition;
	GLuint gNormal;
	GLuint gColorSpec;
	std::weak_ptr<Shader> m_SimpleDepthShader;
	std::weak_ptr<Shader> screenShader;
	list<Node*> drawObjects;		// ��Ҫ��Ⱦ�����弯��
	static map<string, int> textures;
	void filterInit();
	
};
