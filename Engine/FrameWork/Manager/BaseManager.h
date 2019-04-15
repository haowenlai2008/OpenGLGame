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
class BaseManager
{
public:
	float screenWidth;
	float screenHeight;
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
	unsigned int VAO;
	unsigned int EBO;

	float lastFrame;
	float deltaTime;
	float lastX;
	float lastY;
	bool firstMouse;
	float view;

	void BaseInit();//窗口初始化
	void MainLoop();//主循环
	
	
	
	BaseManager();
};