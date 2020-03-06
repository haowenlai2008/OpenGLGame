#include "BaseManager.h"
#include <functional>
#include <string>
#include "Shader.h"
#include "Node.h"
#include "RefManager.h"
#include "RenderManager.h"
#include "LogicManager.h"
#include "Scene.h"
#include "Camera.h"
#include "GameCamera.h"
#include "LightCamera.h"
using namespace std;

BaseManager::~BaseManager()
{
	if (originNode != nullptr)
		originNode->release();
}


std::shared_ptr<GameCamera> BaseManager::getCamera()
{
	return m_pGameCamera;
}

std::shared_ptr<LightCamera> BaseManager::getLightCamera()
{
	return m_pLightCamera;
}

int BaseManager::run()
{
	baseInit();//窗口初始化，键盘、鼠标等事件的绑定
	mainLoop();//渲染相关
	return 0;
}

void BaseManager::processInput(GLFWwindow *window)
{
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, true);

	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	camera.ProcessKeyboard(FORWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	camera.ProcessKeyboard(BACKWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	camera.ProcessKeyboard(LEFT, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	camera.ProcessKeyboard(RIGHT, deltaTime);

	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	saturation += 0.02f;
	//	saturation = saturation > 1.0f ? 1.0f : saturation;
	//	
	//	contrast += 0.02f;
	//	contrast = contrast > 1.0f ? 1.0f : contrast;
	//}

	//if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	saturation -= 0.02f;
	//	saturation = saturation < 0.0f ? 0.0f : saturation;

	//	contrast -= 0.02f;
	//	contrast = contrast < 0.0f ? 0.0f : contrast;
	//}
	m_pKeyboard->processInput(window);
	//m_pKeyboard->haha(window);
}
void BaseManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if (firstMouse)
	//{
	//	lastX = xpos;
	//	lastY = ypos;
	//	firstMouse = false;
	//}

	//float xoffset = xpos - lastX;
	//float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	//lastX = xpos;
	//lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
	//std::cout << "x = " << xoffset << " y = " << yoffset << std::endl;
	m_pMouse->processMessage(window, xpos, ypos);
}
void BaseManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_pMouse->processMouseScroll(window, xoffset, yoffset);
	//camera.ProcessMouseScroll(yoffset);
}
void BaseManager::resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	m_pGameCamera->setAspect((float)width / height);
	m_pLightCamera->setWidth((float)width);
	m_pLightCamera->setHeight((float)height);
}
void BaseManager::runScene(Scene * scene)
{
}
mat4 BaseManager::getViewMat4()
{
	if (!m_pRenderManager)
		return mat4();
	if (m_pRenderManager->getIsShadow())
	{
		return m_pLightCamera->getViewMat4();
		//return m_Camera->getViewXM();
	}
	else
	{
		//return m_LightCamera->getViewXM();
		return m_pGameCamera->getViewMat4();
	}
}
mat4 BaseManager::getProjMat4()
{
	if (!m_pRenderManager)
		return mat4();
	if (m_pRenderManager->getIsShadow())
	{
		return m_pLightCamera->getProjMat4();
		//return m_Camera->getViewXM();
	}
	else
	{
		//return m_LightCamera->getViewXM();
		return m_pGameCamera->getProjMat4();
	}
}
mat4 BaseManager::getViewProjMat4()
{
	if (!m_pRenderManager)
		return mat4();
	if (m_pRenderManager->getIsShadow())
	{
		return m_pLightCamera->getViewProjMat4();
		//return m_Camera->getViewXM();
	}
	else
	{
		//return m_LightCamera->getViewXM();
		return m_pGameCamera->getViewProjMat4();
	}
}
//窗口初始化
void BaseManager::baseInit()
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

	m_pMouse = std::make_unique<MyMouse>();
	m_pKeyboard = std::make_unique<MyKeyboard>();
	m_pGameCamera = std::make_shared<GameCamera>();
	m_pLightCamera = std::make_shared<LightCamera>();
	glfwSetFramebufferSizeCallback(glWindow, [](GLFWwindow* window, int width, int height) { BaseManager::getInstance()->resize_callback(window, width, height); });
	glfwSetCursorPosCallback(glWindow, [](GLFWwindow* window, double xpos, double ypos) {BaseManager::getInstance()->mouse_callback(window, xpos, ypos); });
	glfwSetScrollCallback(glWindow, [](GLFWwindow* window, double xoffset, double yoffset) {BaseManager::getInstance()->scroll_callback(window, xoffset, yoffset); });

	resize_callback(glWindow, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	
	m_pRenderManager = RenderManager::getInstance();
	m_pRefManager = RefManager::getInstance();
	m_pLogicManager = LogicManager::getInstance();
	m_pRenderManager->init();
	m_pRefManager->init();
	m_pLogicManager->init();
	//glEnable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void BaseManager::mainLoop()
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

		RenderManager::getInstance()->bindFrameBuffer();//绑定帧缓冲
		glEnable(GL_DEPTH_TEST);
		
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(glWindow);

		// 设置鼠标键盘当前状态
		setKeyboardState(m_pKeyboard->getState());
		setMouseState(m_pMouse->getState());

		// 游戏相机对鼠标键盘的处理
		m_pGameCamera->processMouse(m_MouseState, MyMouse::State(), deltaTime);
		m_pGameCamera->processKeyBoard(m_KeyboardState, deltaTime);


		m_pRefManager->update();	//引用计数更新
		m_pLogicManager->update(originNode, deltaTime);
		m_pLogicManager->lateUpdate(originNode, deltaTime);

		m_pGameCamera->updateViewProjMatrix();
		m_pLightCamera->updateViewProjMatrix();

		m_pRenderManager->draw();
		

		
		RenderManager::getInstance()->filterUse();	//使用滤镜
		glfwSwapBuffers(glWindow);
		glfwPollEvents();

	}
	glfwTerminate();
}
