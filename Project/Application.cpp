#include<iostream>
#define GLEW_STATIC
//#include <glew.h>
//#include <glfw3.h>
#include "glfw3.h"
#include "glad.h"
using namespace std;

int main(int argc, char** argv[])
{
	glfwInit();//≥ı ºªØ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//≈‰÷√GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//≈‰÷√GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}