#pragma once
#include "Shader.h"
#include "Camera.h"
#include "const.h"
#include <glfw3.h>
#include <glad.h>
#include <stb_image.h>
#include <iostream>

class GLFWwindow;
class Node;
class Scene;
class RenderManager;
class RefManager;
class LogicManager;

class BaseManager
{
public:
	float screenWidth;
	float screenHeight;
	float saturation;
	float contrast;
	static BaseManager* m_instance;
	~BaseManager();
	static BaseManager* getInstance();
	static Camera* getCamera();
	int Run();
	void ProcessInput(GLFWwindow *window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void runScene(Scene* scene);
private:
	GLFWwindow* glWindow;
	Camera camera;
	Node* originNode;

	float lastFrame;
	float deltaTime;
	float lastX;
	float lastY;
	bool firstMouse;
	float view;

	RefManager* refManager;
	RenderManager* renderManager;
	LogicManager* logicManager;

	void BaseInit();//窗口初始化
	void MainLoop();//主循环

	BaseManager();
};