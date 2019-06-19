#include "BaseManager.h"
#include "Shader.h"
#include "Node.h"
#include "RefManager.h"
#include "RenderManager.h"
#include "LogicManager.h"
#include "Scene.h"
#include <functional>
#include <string>
using namespace std;
BaseManager* BaseManager::m_instance = nullptr;


BaseManager::BaseManager()
{
}


BaseManager::~BaseManager()
{
	if (originNode != nullptr)
		originNode->release();

}

BaseManager * BaseManager::getInstance()
{
	if (!m_instance)
		m_instance = new(std::nothrow) BaseManager();
	return m_instance;
}

Camera * BaseManager::getCamera()
{
	return &BaseManager::getInstance()->camera;
}

int BaseManager::Run()
{
	BaseInit();//窗口初始化，键盘、鼠标等事件的绑定
	MainLoop();//渲染相关
	return 0;
}

void BaseManager::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		saturation += 0.02f;
		saturation = saturation > 1.0f ? 1.0f : saturation;
		
		contrast += 0.02f;
		contrast = contrast > 1.0f ? 1.0f : contrast;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		saturation -= 0.02f;
		saturation = saturation < 0.0f ? 0.0f : saturation;

		contrast -= 0.02f;
		contrast = contrast < 0.0f ? 0.0f : contrast;
	}
		
}
void BaseManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void BaseManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void BaseManager::runScene(Scene * scene)
{
}
//窗口初始化
void BaseManager::BaseInit()
{
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	screenWidth = 1280.0f;
	screenHeight = 720.0f;
	//创建窗口
	glWindow = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
	if (glWindow == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(glWindow);
	//glEnable(GL_MULTISAMPLE);//多重采样抗锯齿
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float lastX = screenWidth / 2.0f;
	float lastY = screenHeight / 2.0f;
	bool firstMouse = true;
	glfwSetFramebufferSizeCallback(glWindow, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
	glfwSetCursorPosCallback(glWindow, [](GLFWwindow* window, double xpos, double ypos) {BaseManager::getInstance()->mouse_callback(window, xpos, ypos); });
	glfwSetScrollCallback(glWindow, [](GLFWwindow* window, double xoffset, double yoffset) {BaseManager::getInstance()->scroll_callback(window, xoffset, yoffset); });

	glEnable(GL_DEPTH_TEST);
	renderManager = RenderManager::getInstance();
	refManager = RefManager::getInstance();
	logicManager = LogicManager::getInstance();
	renderManager->init();
	refManager->init();
	logicManager->init();
	//glEnable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BaseManager::MainLoop()
{
	saturation = 0.0f;
	contrast = 0.0f;

	originNode = Node::create();//游戏对象树的根
	originNode->retain();
	Scene* scene = Scene::create();
	originNode->addChild(scene);
	glEnable(GL_DEPTH_TEST);	//开启深度测试
	glEnable(GL_CULL_FACE);		//开启面剔除
	while (!glfwWindowShouldClose(glWindow))
	{
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(glWindow);
		RenderManager::getInstance()->bindFrameBuffer();//绑定帧缓冲
		glEnable(GL_DEPTH_TEST);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		logicManager->update(originNode, deltaTime);
		renderManager->update(originNode);
		
		refManager->update();	//引用计数更新
		RenderManager::getInstance()->update(originNode);	//渲染
		
		RenderManager::getInstance()->filterUse();	//使用滤镜
		glfwSwapBuffers(glWindow);
		glfwPollEvents();

	}
	glfwTerminate();
}
