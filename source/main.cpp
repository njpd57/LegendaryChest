#include "main.hpp"
#include "Engine.hpp"
int main(void)
{
	Engine MainEngine;
	MainEngine.Intro();

	while(MainEngine.running)
	{
		MainEngine.Input();
		SDL_Flip(MainEngine.screen);
	}

	MainEngine.Quit();	
	return 0;
}
