#include "SDLUtility.hpp"
#include "Engine.hpp"


Engine::Engine()
{
    romfsInit();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

    SDL_ShowCursor(SDL_DISABLE);
    screen      = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_DUALSCR |SDL_FITHEIGHT);// SDL_FITWIDTH);
    running     = true;
    screenRect.x= 0;
    screenRect.y= 0;
    screenRect.w= SCREEN_WIDTH;
    screenRect.h= SCREEN_HEIGHT;

    font = TTF_OpenFont("romfs:/Graphics/Fonts/GameFont.ttf",16);
    TextColor = {255,255,255};
    ClearColor  = SDL_MapRGB(screen->format,0,0,0);
    SDL_FillRect(screen,&screenRect,ClearColor);
    SDL_Flip(screen);

	GameState=S_Intro;

	//FADEOUT/FADEIN

	



}

void Engine::Init(){};

void Engine::Quit()
{
    SDL_FreeSurface(IntroImage);
    Mix_FreeMusic(CastleSong);

    TTF_CloseFont(font);
    TTF_Quit();    
    Mix_CloseAudio();

    SDL_Quit();
}

//GameStates
void Engine::Intro()
{
    IntroImage=loadImage("romfs:/Graphics/Logos/studioLogo.png");
    applySurface(0,0,IntroImage,screen);
	SDL_Flip(screen);
	bool Done(false);
	while(!Done)
	{
		SDL_Delay(5000);
		Done=true;
	}
	if(Done)GameState=S_StartMenu;
}

void Engine::StartMenu()
{
	ClearScreen();
	
}
void Engine::Input()
{
    SDL_Event event;

	while(SDL_PollEvent(&event))
	    {
			switch(event.type)
			{
				case SDL_KEYDOWN:
				
					switch(event.key.keysym.sym)
					{
						case SDLK_a:
							if(Mix_PausedMusic() == 1)
							{
								Mix_ResumeMusic();
							}
							else Mix_PauseMusic();
							break;
						case SDLK_b:

							
							break;
						case SDLK_x:
							
							break;
						case SDLK_y:
							
							break;
						case SDLK_l:
							
							break;
						case SDLK_r:
							
							break;
						case SDLK_RETURN:
							
							running=false;
							break;
						case SDLK_ESCAPE:
							
							break;
						case SDLK_LEFT:
							
							break;
						case SDLK_RIGHT:
							
							break;
						case SDLK_UP:
							
							break;
						case SDLK_DOWN:
							
							break;
						default:
							break;
					}					
					break;
				case SDL_KEYUP:
					break;
				case SDL_MOUSEMOTION:
					mouseX=event.motion.x;
					mouseY=event.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT)running=false;
				default:
					break;
			}
		} 
}

void Engine::ClearScreen()
{
	SDL_FillRect(screen,&screenRect,ClearColor);
	SDL_Flip(screen);
}
void Engine::fadeOut()
{
	F_Alpha=255;
	F_Done=true;

	fadeSurface=SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA,400,480,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
	SDL_Surface* fadeSurface2 = SDL_DisplayFormat( fadeSurface );

	F_TimerStart=SDL_GetTicks();

	while(!F_Done)
	{
	}
}