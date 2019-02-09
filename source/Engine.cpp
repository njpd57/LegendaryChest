#include "SDLUtility.hpp"
#include "Engine.hpp"
#include "Npc.hpp"
#include "Database.hpp"



Engine::Engine()
{
    romfsInit();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	

    SDL_ShowCursor(SDL_DISABLE);
    screen      = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_DUALSCR |SDL_FITHEIGHT);// SDL_FITWIDTH);
    
    screenRect.x= 0;
    screenRect.y= 0;
    screenRect.w= SCREEN_WIDTH;
    screenRect.h= SCREEN_HEIGHT;

    font = TTF_OpenFont("romfs:/Graphics/Fonts/GameFont.ttf",16);
    TextColor = {255,255,255};
    ClearColor  = SDL_MapRGB(screen->format,0,0,0);
    SDL_FillRect(screen,&screenRect,ClearColor);
    SDL_Flip(screen);

	GameState=S_StartMenu;

	//FADEOUT/FADEIN

	



}

void Engine::Init()
{
	loadNpc();
	LoadImages();
	gameTitleFrame=0;
	running     = true;
	
};

void Engine::Quit()
{
	SDL_FreeSurface(gameTitle);

    TTF_CloseFont(font);
    TTF_Quit();    
    Mix_CloseAudio();

    SDL_Quit();
}

void Engine::GameLoop()
{
	ClearScreen();
	while(running)
	{
		while(SDL_PollEvent(&E_event))
		{
			Input();
		}		
		Update();
		Render();
	}
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
		SDL_Delay(3000);
		Done=true;
	}
	if(Done)
	{
		SDL_FreeSurface(IntroImage);
	}
}

void Engine::StartMenu()
{
	ClearScreen();
	SDL_Surface* MenuScreen=loadImage("romfs:/Graphics/Ui/WhiteLaion.png");
	applySurface(0,0,MenuScreen,screen);
	SDL_Flip(screen);
	bool Done(false);
	while(!Done)
	{
		SDL_Delay(3000);
	}
}
void Engine::Input()
{
	switch(GameState)
	{
		case S_StartMenu:
			break;
		default:
			break;
	}
}
void Engine::Update()
{
	switch(GameState)
	{
		case S_StartMenu:
			applySurface(0,85,gameTitle,screen,&gameTitleRect[gameTitleFrame]);//gameTitleFrame]);			
			gameTitleFrame++;
			if(gameTitleFrame>=10)gameTitleFrame=0;
			break;
		default:
			break;
	}
}
void Engine::Render()
{
	SDL_Flip(screen);
}
void Engine::Battle_Demo()
{
	
	Slime.SetXY(64,176);
	SlimePlayer.SetXY(256,176);
	ClearScreen();
	SDL_Surface* BattleBack=loadImage("romfs:/Graphics/Battlebacks/Forres_fxt.png");
	applySurface(0,0,BattleBack,screen);
	SDL_Flip(screen);
	bool BattleDone(false);
	int i,j;
	while(!BattleDone)
	{
		j++;
		if(j>=3)
		{
			j=0;
			i++;
		}
		if(i>=5)i=0;
		applySurface(0,0,BattleBack,screen);
		applySurface(Slime.x,Slime.y,Slime.npcSurface,screen,&Slime.npcFrame[i]);
		applySurface(SlimePlayer.x,SlimePlayer.y,SlimePlayer.npcSurface,screen,&SlimePlayer.npcFrame[i]);
		Slime.x++;
		if(Slime.x>=400)Slime.x=0;
		SDL_Flip(screen);
	}
	
	BattleDone=true;

	if(BattleDone)
	{
		ClearScreen();
		SDL_FreeSurface(BattleBack);
		SDL_FreeSurface(Slime.npcSurface);
		SDL_Delay(1000);
		SDL_Flip(screen);
		running=false;
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


//INPUT
/*
void Engine::Menu_Input()
{
	switch(E_event.type)
	{
		case SDL_KEYDOWN:		
			switch(E_event.key.keysym.sym)
			{
				case SDLK_a:
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
				mouseX=E_event.motion.x;
				mouseY=E_event.motion.y;
				break;
		case SDL_MOUSEBUTTONDOWN:
				//if(event.button.button == SDL_BUTTON_LEFT)break;
				break;
		default:
				break;
	}
}
*/

//LoadImages
void Engine::LoadImages()
{

	gameTitle=loadImage("romfs:/Graphics/Logos/gameTitle.png");
	
	for(int i=0;i<=10;i++)
	{
		gameTitleRect[i].w = 400;
		gameTitleRect[i].h = 70;
		gameTitleRect[i].x = 0;
		gameTitleRect[i].y = i*70;
	};

	
}