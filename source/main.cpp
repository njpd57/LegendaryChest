#include "main.hpp"
#include "Engine.hpp"
int main(void)
{
	Engine MainEngine;
	MainEngine.Init();
	MainEngine.Intro();
	MainEngine.GameLoop();
	MainEngine.Quit();	
	return 0;
}
