#include "main.hpp"
#include "Engine.hpp"
int main(void)
{
	Engine MainEngine;

	while(MainEngine.running)
	{
		switch(MainEngine.GameState)
		{
			case S_StartMenu:
				MainEngine.StartMenu();
				break;
			case S_OptionMenu:
				break;
			case S_InGame:
				break;
			case S_Credits:
				break;
			case S_Intro:
				MainEngine.Intro();
				break;
			default:
				break;
		}
		SDL_Flip(MainEngine.screen);
	}

	MainEngine.Quit();	
	return 0;
}
