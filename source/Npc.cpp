#include "main.hpp"
#include "Npc.hpp"

extern SDL_Surface* loadImage(std::string ImageName);
extern void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* dest,SDL_Rect* clip=NULL);

#define IMAGE_DELAY 1
npc::npc(std::string n_name,int n_h,int n_w,int n_frames)
{
    NAME    =   n_name;
    x       =   0;
    y       =   0;
    h       =   n_h;
    w       =   n_w;
    frames  =   n_frames;
    ALIVE   =   true;

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
void npc::SetATTR(int T_HP,int T_MP,int T_STR,int T_DEF)
{
    HP  =   T_HP;
    MP  =   T_MP;   
    STR =   T_STR;
    DEF =   T_DEF;
};
void npc::SetXY(int t_x,int t_y)
{
    x   =   t_x;
    y   =   t_y;
}
void npc::Animate()
{
    Delay++;
    if(Delay>= IMAGE_DELAY)
    {
        CurrFrame++;
        Delay=0;
    }
    if(CurrFrame>=frames)CurrFrame=0;
}
void npc::Update(SDL_Surface* destin)
{
    Animate();
    applySurface(x,y,npcSurface,destin,&npcFrame[CurrFrame]);
}

int npc::Attack()
{
    int Damage = rand () % STR;
    return Damage;
}

int npc::Attacked(int DMG)
{
    int Protected = rand() % DEF;
    int Damage = DMG - DEF;
    if(Damage > 0)HP-=Damage;
}
