#define GLEW_STATIC
#include <iostream>
#include "BaseManager.h"
#include <Windows.h>


int main()
{
	HMODULE hMod = LoadLibraryA("C:\\Program Files\\RenderDoc\\x86\\renderdoc.dll");
	BaseManager::getInstance()->run();
	return 0;
}
