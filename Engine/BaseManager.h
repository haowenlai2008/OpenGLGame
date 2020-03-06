#pragma once
#include "func.h"
#include "Singleton.h"
#include "MyMouse.h"
#include "MyKeyboard.h"
class GLFWwindow;
class Node;
class Scene;
class RenderManager;
class RefManager;
class LogicManager;
class GameCamera;
class LightCamera;
class BaseManager : public Singleton<BaseManager>
{
public:
	friend class Singleton<BaseManager>;
	float screenWidth;
	float screenHeight;
	float saturation;
	float contrast;
	std::shared_ptr<GameCamera> getCamera();
	std::shared_ptr<LightCamera> getLightCamera();
	int run();
	void processInput(GLFWwindow *window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void resize_callback(GLFWwindow* window, int width, int height);
	void runScene(Scene* scene);
	mat4 getViewMat4();	// 获得观察矩阵
	mat4 getProjMat4();	// 获得裁剪矩阵
	mat4 getViewProjMat4();	// 获得观察矩阵裁剪矩阵的乘积
	LL_SYNTHESIZE(MyKeyboard::State, m_KeyboardState, KeyboardState);
	LL_SYNTHESIZE(MyMouse::State, m_MouseState, MouseState);
	~BaseManager();
private:
	std::unique_ptr<MyMouse> m_pMouse;
	std::unique_ptr<MyKeyboard> m_pKeyboard;
	std::shared_ptr<GameCamera> m_pGameCamera;
	std::shared_ptr<LightCamera> m_pLightCamera;
	GLFWwindow* glWindow;
	Node* originNode;
	float lastFrame;
	float deltaTime;
	float lastX;
	float lastY;
	bool firstMouse;
	float view;

	RefManager* m_pRefManager;
	RenderManager* m_pRenderManager;
	LogicManager* m_pLogicManager;

	void baseInit();//窗口初始化
	void mainLoop();//主循环
};