#include "main.hpp"
#include "Npc.hpp"

extern SDL_Surface* loadImage(std::string ImageName);

npc::npc(int n_h,int n_w,int n_frames)
{
    x       =   0;
    y       =   0;
    h       =   n_h;
    w       =   n_w;
    frames  =   n_frames;

    for(int i=0;i<=frames;i++)
    {
        npcFrame[i].h = h;
        npcFrame[i].w = w;
        npcFrame[i].x = i*w;
        npcFrame[i].y = 0;
    }
}

void npc::SetImage(std::string image)
{
    npcSurface=loadImage(image);
}

