#include<iostream>
//#define GLEW_STATIC
//#include <glew.h>
//#include <glfw3.h>
#include "BaseManager.h"
using namespace std;

int main(int argc, char** argv[])
{
	return BaseManager::getInstance()->Run();
}