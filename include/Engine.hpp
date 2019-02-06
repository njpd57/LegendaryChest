#include "main.hpp"
#ifndef ENGINE_H
#define ENGINE_H


//Game System Options
#define SCREEN_HEIGHT       480
#define SCREEN_WIDTH        400
#define SCREEN_BPP          32
#define SUB_SCREEN_WIDTH    320
#define SCREEN_FPS          60

//GAMESTATES
#define StartMenu   0
#define OptionMenu  1
#define InGame      2
#define Credits     3

class Engine
{
    public:
        Engine();
        void Init();
        void Render();
        void Update();
        void Input();
        void Quit();


        bool running;

        //Graphics
        SDL_Surface* screen;
        SDL_Rect    screenRect;
        
        //Texts
        TTF_Font* font;
        SDL_Color TextColor;

        //GameStates
        void Intro();
        int mouseX;
        int mouseY;

        int frame;
        

    private:
        int GameState;
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

};

#endif