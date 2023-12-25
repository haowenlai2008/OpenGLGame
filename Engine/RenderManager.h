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
	GLuint shadowMapTexture = -1;
	GLuint environmentMapIBL = -1;		// ������ͼ
	GLuint scenePassTexture = -1;		// ǰ����Ⱦ�������
	GLuint irradianceMapIBL = -1;		// ������ͼ��������õ�irradiance map
	GLuint prefilterMapIBL = -1;		// irradiance map���ɵ�mipmap
	GLuint brdfLUT = -1;				// roughness-cos brdf��ӳ��
	GLuint afterPossprocessTexture = -1;		// ����������
	GLuint gBuffer_Position = -1;				// GBuffer λ��
	GLuint gBuffer_Normal = -1;					// GBuffer ����
	GLuint gBuffer_Albedo = -1;					// GBuffer ������
	GLuint gBuffer_MetallicRoughness = -1;		// GBuffer mrģ�Ͳ���
	GLuint gBuffer_PosLightSpace = -1;			// GBuffer ��Դ�ռ�����
	GLuint gBuffer_ViewPos = -1;				// GBuffer �۲�ռ�λ��
	GLuint gBuffer_ViewNormal = -1;				// GBuffer �۲�ռ䷨��
	GLuint ssao_noise = -1;						// ssao���������ת����
	GLuint ssao_Texture = -1;					// ssao���
	GLuint ssao_BlurTexture = -1;				// ssaoģ������
};

// ȫ��buffer
struct GlobleBufferStructure
{
	GLuint shadowMapBuffer = -1;
	GLuint environmentBufferIBL = -1;
	GLuint scenePassBuffer = -1;
	GLuint afterPossprocessBuffer = -1;
	GLuint gBuffer = -1;
	GLuint ssaoFrameBuffer = -1;
	GLuint ssaoBlurFrameBuffer = -1;
};

class RenderManager : public Singleton<RenderManager>
{
public:
	friend class Singleton<RenderManager>;
	list<Node*> drawObjects;		// ��Ҫ��Ⱦ�����弯�ϣ�ÿ֡���
	Node* skyBox;				// ��պе��������
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
