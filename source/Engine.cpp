#include "SDLUtility.hpp"
#include "Engine.hpp"
#include "Sounds.hpp"
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
	SoundInit();
    screen      = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_DUALSCR |SDL_FITHEIGHT );// SDL_FITWIDTH);
    
    screenRect.x= 0;
    screenRect.y= 0;
    screenRect.w= SCREEN_WIDTH;
    screenRect.h= SCREEN_HEIGHT;

    font = TTF_OpenFont("romfs:/Graphics/Fonts/GameFont.ttf",16);
    TextColor = {255,255,255};
    ClearColor  = SDL_MapRGB(screen->format,0,0,0);
    SDL_FillRect(screen,&screenRect,ClearColor);
    SDL_Flip(screen);
	srand (time(NULL));
	
	C_ChangeState	=	true;
	C_UnloadState	= 	false;
	running     	=	true;

	//FADEOUT/FADEIN
	gameTitleFrame=0;
	cursorFrame=0;
	C_Selected=false;
	Cursor_Option=0;

	GameState=S_StartMenu;

	//DEBUG
	//GameState=S_BattleDemo;

	



}

void Engine::Init()
{

};

void Engine::Quit()
{
	ClearAllSounds();

    TTF_CloseFont(font);
    TTF_Quit();    
    Mix_CloseAudio();

    SDL_Quit();
}

void Engine::GameLoop()
{
	while(running)
	{
		LoadState(GameState);
		
		while(SDL_PollEvent(&E_event))
		{
			Input();
		}		
		Update();
		Render();

		UnloadState();
	}
}


//				GAMESTATES			//

//		INTRO		//
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

//		BATTLE		//

void Engine::Battle()
{
	
	if(!BattleBackLoaded)
	{
		LoadBattleBack();
	}
	SDL_BlitSurface(BattleBack,NULL,screen,NULL);
	switch(MenuState)
	{
		case B_Menu:
			SDL_BlitSurface(BottomMenu[0],NULL,screen,&BottomMenuRect);
			break;
		case B_Objects:
			SDL_BlitSurface(BottomMenu[1],NULL,screen,&BottomMenuRect);
			break;
		case B_Habilities:
			SDL_BlitSurface(BottomMenu[2],NULL,screen,&BottomMenuRect);
			break;
	}
	
	
	P_Player.Update(screen);
	Slime.Update(screen);
}
void Engine::LoadBattleBack()
{
	switch(T_BattleBack)
	{
		case BB_DEMOFORREST:
			BattleBack=loadImage("romfs:/Graphics/Battlebacks/Forres_fxt.png");
			BattleBackLoaded=true;
			break;
		default:
			BattleBackLoaded=true;
			break;
	}
}

/////////////////////////////////////////////////////


void Engine::Input()
{
	switch(GameState)
	{
		case S_StartMenu:
			Menu_Input();
			break;
		case S_BattleDemo:
			DemoBattle_Input();
			break;
		case S_Battle:
			DemoBattle_Input();
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
			
			applySurface(0,85,gameTitle,screen,&gameTitleRect[gameTitleFrame]);
			applySurface(100,310,menuOptions,screen);
			applySurface(Cursor_X,Cursor_Y,cursor,screen,&cursorRect[cursorFrame]);

			//ANIMATE
			gameTitleFrame++;
			cursorFrame++;

			if(gameTitleFrame>=9)gameTitleFrame=0;
			if(cursorFrame>=21)cursorFrame=0;

			//Cursor
			switch(Cursor_Option)
			{
				case 0:
					Cursor_X=142;
					Cursor_Y=335;
					break;
				case 1:
					Cursor_X=154;
					Cursor_Y=351;
					break;
				case 2:
					Cursor_X=166;
					Cursor_Y=367;
					break;
			}

			if(C_Selected)
			{
				switch(Cursor_Option)
				{
					case 0:
						ChangeState(S_Battle);						
						break;
					case 1:
						C_Selected=false;
						break;
						/*
						GameState=S_OptionMenu;
						C_ChangeState=true;
						break;
						*/
					case 2:
						running=false;
						break;
				}
				/*

				*/
				C_Selected=false;
			}
			break;

		case S_BattleDemo:
			applySurface(0,0,demoBattleBack,screen);
			Slime.Update(screen);
			DemoPlayer.Update(screen);
			break;
		case S_Battle:
			Battle();
		default:
			break;
	}
}
void Engine::Render()
{
	SDL_Flip(screen);
}
/*
void Engine::Battle_Demo()
{
	
	Slime.SetXY(64,176);
	SlimePlayer.SetXY(256,176);
	ClearScreen();
	
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
*/
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
void Engine::Menu_Input()
{
	switch(E_event.type)
	{
		case SDL_KEYDOWN:		
			switch(E_event.key.keysym.sym)
			{
				case SDLK_a:
						PlaySound(FX_SELECTED);
						C_Selected=true;

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
						PlaySound(FX_SELECT);
						Cursor_Option--;
						if(Cursor_Option<0)Cursor_Option=2;	
						break;
				case SDLK_DOWN:
						PlaySound(FX_SELECT);
						Cursor_Option++;
						if(Cursor_Option>2)Cursor_Option=0;
						break;
				default:
						break;
			}					
			break;
		case SDL_KEYUP:
				break;
		case SDL_MOUSEMOTION:
				break;
		case SDL_MOUSEBUTTONDOWN:
				break;
		default:
				break;
	}
}
void Engine::DemoBattle_Input()
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
						ChangeState(S_StartMenu);
						break;
				case SDLK_ESCAPE:			
						break;
				case SDLK_LEFT:
						P_Player.moveLeft=true;
						break;
				case SDLK_RIGHT:
						P_Player.moveRight=true;
						break;
				case SDLK_UP:
						P_Player.moveUp=true;
						break;
				case SDLK_DOWN:
						P_Player.moveDown=true;
						break;
				default:
						break;
			}					
			break;
		case SDL_KEYUP:
				switch(E_event.key.keysym.sym)
				{
				case SDLK_LEFT:
						P_Player.moveLeft=false;
						break;
				case SDLK_RIGHT:
						P_Player.moveRight=false;
						break;
				case SDLK_UP:
						P_Player.moveUp=false;
						break;
				case SDLK_DOWN:
						P_Player.moveDown=false;
						break;
				default:
						break;
				}					
				break;
		case SDL_MOUSEMOTION:
				break;
		case SDL_MOUSEBUTTONDOWN:
				break;
		default:
				break;
	}
}



//INPUT EXAMPLE




void Engine::LoadState(int newState)
{
	if(C_ChangeState)
	{
		loadScreen=loadImage("romfs:/Graphics/Ui/loadscreen.png");
		applySurface(0,0,loadScreen,screen);
		SDL_Flip(screen);
		switch(newState)
		{
			case S_StartMenu:
				
				Menu_Background=loadImage("romfs:/Graphics/Ui/Menu.png");
				gameTitle=loadImage("romfs:/Graphics/Logos/gameTitle.png");
				for(int i=0;i<=9;i++)
				{
					gameTitleRect[i].w = 400;
					gameTitleRect[i].h = 70;
					gameTitleRect[i].x = 0;
					gameTitleRect[i].y = i*70;
				};

				cursor=loadImage("romfs:/Graphics/Sprites/Cursor.png");
				for(int i=0;i<=21;i++)
				{
					cursorRect[i].w = 16;
					cursorRect[i].h	= 16;
					cursorRect[i].x = 16*i;
					cursorRect[i].y = 0;
				}
				
				menuOptions=loadImage("romfs:/Graphics/Ui/menuu.png");

				//APPLY
				applySurface(0,0,Menu_Background,screen);

				LoadSong(MUS_ANOTHERCASTLE);
				PlaySong();
				
				break;

			case S_BattleDemo:
				Data_loadNpc();
				Data_loadPlayer();
				demoBattleBack=loadImage("romfs:/Graphics/Battlebacks/Forres_fxt.png");

				Slime.SetXY(115,184);
				DemoPlayer.SetXY(241,183);
				DemoPlayer.moveLeft=true;
				break;
			case S_Battle:
				Data_loadNpc();
				Data_loadPlayer();

				//Lo Tiene Que Hacer Una Funcion!!!!				
				MenuState=0;
				PlayerTurn=true;
				BattleBackLoaded=false;
				T_BattleBack=BB_DEMOFORREST;
				Slime.SetXY(115,184);
				P_Player.SetXY(241,183);
				P_Player.moveLeft=true;
				////////////////////////
				
				
				BottomMenu[0]=loadImage("romfs:/Graphics/Ui/BattleMenu.png");
				BottomMenu[1]=loadImage("romfs:/Graphics/Ui/BattleMenuObjects.png");
				BottomMenu[2]=loadImage("romfs:/Graphics/Ui/BattleMenuHabilities.png");
				BottomMenuRect.x=40;
				BottomMenuRect.y=240;
				
		}
		C_ChangeState=false;
		SDL_Delay(1000);
		
	}
	
}

void Engine::UnloadState()
{
	if(C_UnloadState)
	{
		switch(OldState)
		{
			case S_StartMenu:
				C_Selected=false;
				Cursor_Option=0;
				Mix_HaltMusic();
				SDL_FreeSurface(Menu_Background);
				SDL_FreeSurface(gameTitle);
				SDL_FreeSurface(menuOptions);
				UnloadSong();
				break;		
			case S_Battle:
				SDL_FreeSurface(BattleBack);
				SDL_FreeSurface(BottomMenu[0]);
				SDL_FreeSurface(BottomMenu[1]);
				SDL_FreeSurface(BottomMenu[2]);
			default:
				break;
		}

		C_UnloadState=false;

	}
}

void Engine::ChangeState(int newState)
{
	OldState=GameState;
	GameState=newState;
	C_ChangeState=true;
	C_UnloadState=true;
}