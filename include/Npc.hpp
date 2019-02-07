#include "main.hpp"

#ifndef NPC_H
#define NPC_H

class npc
{
    public:
        npc(int n_h,int n_w,int n_frames);

        void SetImage(std::string image);


        int x;
        int y;
        int h;
        int w;
        int frames;
        SDL_Surface* npcSurface;
        SDL_Rect npcFrame[10];


    private:
        
        

};

#endif