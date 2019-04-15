#define GLEW_STATIC
#include <iostream>
#include "BaseManager.h"



int main()
{
	BaseManager::getInstance()->Run();
	return 0;
}
