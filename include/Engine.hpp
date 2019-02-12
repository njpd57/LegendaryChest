#include "main.hpp"
#include "Player.hpp"
#ifndef ENGINE_H
#define ENGINE_H



//Game System Options
#define SCREEN_HEIGHT       480
#define SCREEN_WIDTH        400
#define SCREEN_BPP          32
#define SUB_SCREEN_WIDTH    320
#define SCREEN_FPS          60

//GAMESTATES
#define S_StartMenu   0
#define S_OptionMenu  1
#define S_InGame      2
#define S_Credits     3
#define S_Intro       4

#define S_Battle      5
#define S_Indoor      6
#define S_Map         7
#define S_BattleDemo  8

//MENUSTATES
#define B_Menu       0
#define B_Objects    1
#define B_Habilities 2

class Engine
{
    public:
        Engine();
        void Init();
        void Render();
        void Update();
        void Input();
        void Quit();
        void GameLoop();
        void ClearScreen();
        void Intro();
        



        bool running;

        //Graphics//
        SDL_Surface* screen;
        SDL_Rect    screenRect;
        ///////////////////////

        //Texts//
        TTF_Font* font;
        SDL_Color TextColor;
        //////////////////////

        //GameStates//
            //CONTROL
            int GameState;
            int OldState;
            bool C_ChangeState;
            bool C_UnloadState;
            void LoadState(int newState);
            void UnloadState();
            void ChangeState(int newState);
            
            ////////////////////////////////

            //STARTMENU//////////////////

            SDL_Surface* Menu_Background;

            SDL_Surface* gameTitle;
            SDL_Rect     gameTitleRect[10];
            int          gameTitleFrame;

            SDL_Surface* cursor;
            SDL_Rect     cursorRect[21];
            int          cursorFrame;
            int Cursor_X;
            int Cursor_Y;
            bool C_Selected;
            int Cursor_Option;
            ///////////////////////////////

            SDL_Surface* menuOptions;

            //Battle System

            int MenuState;
            void Battle();  //(SDL_Surface* Battleback,SDL_Music BattleMusic,int EnemyCount,npc Enemys[5])
            void LoadBattleBack();
            int T_BattleBack;
            SDL_Surface* BattleBack;
            bool BattleBackLoaded;
            bool PlayerTurn;

                //  TEXT    //

                //  IMAGES  //
                SDL_Surface* BottomMenu[3];
                SDL_Rect     BottomMenuRect;
            ////////////////////////

            //INDOOR

            void Indoor();

            //BATTLEDEMO
            void Battle_Demo();
            SDL_Surface* demoBattleBack;

            //LOADSCREEN
            SDL_Surface* loadScreen;

            
        int mouseX;
        int mouseY;


        void LoadImages();
        
        //Time
        Uint32 start;

        //Input
        void Menu_Input();
        void DemoBattle_Input();

    private:
        
        Uint32 ClearColor;
        SDL_Surface* IntroImage;
        Mix_Music* CastleSong;

        //FADEOUT/FADEIN

        int F_Alpha;
        bool F_Done;
        int F_TimerStart;
        SDL_Surface* fadeSurface;

        void fadeIn();
        void fadeOut();

        //Event Sys
        SDL_Event E_event;

        
};

#endif