#include "main.hpp"

#ifndef NPC_H
#define NPC_H

class npc
{
    public:
        npc(std::string n_name,int n_h,int n_w,int n_frames);

        void SetImage(std::string image);
        void SetXY(int t_x,int t_y);
        void SetATTR(int T_HP,int T_MP,int T_STR,int T_DEF);


        
        //IMAGE INFO
        int h;
        int w;
        int frames;
        SDL_Surface* npcSurface;
        SDL_Rect npcFrame[10];
        //POS
        int x;
        int y;
        //STATS
        std::string NAME;
        bool ALIVE;
        int HP;
        int MP;
        int STR;
        int DEF;


    private:
        
        

};

#endif