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
	void ShaderCompile();
	void Render();
	void Render2();
	void Render3();
	unsigned int shaderProgram;
	unsigned int VAO;
	BaseManager();
};

