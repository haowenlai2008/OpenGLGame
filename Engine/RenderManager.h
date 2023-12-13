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
// ȫ������
struct GlobalTextureStructure
{
	GLuint shadowMapTexture;
	GLuint environmentMapIBL;
	GLuint scenePassTexture;
	GLuint irradianceMapIBL;
	GLuint prefilterMapIBL;
	GLuint brdfLUT;
};

// ȫ��buffer
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
	list<Node*> drawObjects;		// ��Ҫ��Ⱦ�����弯�ϣ�ÿ֡���
	list<std::shared_ptr<RP_RenderPass>> m_RenderPassList;	// ����
	static GlobalTextureStructure globleTexture;	// ȫ������
	static GlobleBufferStructure globalBuffer;		// ȫ��Buffer

	void init();
	void draw();
	void addDrawNode(Node* node);
private:
	// �ӳ���Ⱦ��
	GLuint gPosition;
	GLuint gNormal;
	GLuint gColorSpec;

};
