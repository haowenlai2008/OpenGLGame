#pragma once
class GLFWwindow;
class BaseManager
{
public:
	static BaseManager* m_instance;
	~BaseManager();
	static BaseManager* getInstance();
	int Run();
private:
	GLFWwindow* glWindow;
	void BaseInit();
	void MainLoop();
	void ProcessInput(GLFWwindow *window);
	void RenderInit();
	void Render();
	void Render2();
	unsigned int shaderProgram;
	unsigned int VAO;
	BaseManager();
};

