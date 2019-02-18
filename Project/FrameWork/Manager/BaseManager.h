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
	//������ɫ��
	template <typename S1, typename S2 = std::string>
	void ShaderCompile(S1&& vs, S2&& fs)
	{
		Shader shader(std::forward<std::string>(vs), std::forward<std::string>(fs));
		shaderProgram = shader.ID;
		shader.use();
	};
	void Render();
	void Render2();
	void Render3();
	void Render4();//��ɫ������
	void Render5();//������
	unsigned int shaderProgram;
	unsigned int VAO;
	BaseManager();
};