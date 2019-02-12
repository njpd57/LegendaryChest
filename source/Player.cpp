#include "Player.hpp"
#include "main.hpp"


extern SDL_Surface* loadImage(std::string ImageName);
extern void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* dest,SDL_Rect* clip=NULL);


Player::Player()
{
    Name    =   "Logic";
    LVL     =   1;
    HP      =   10;
    MP      =   10;
    STR     =   5;
    DEF     =   5;
    Alive   =   true;
    x       =   0;
    y       =   0;

    ANIM_Frames     =   0;
    ANIM_Delay =   0;    
    IMG_Frames  =   11;
    
    for(int i=0;i<=IMG_Frames;i++)
    {
        Rect[i].h   =   32;
        Rect[i].w   =   32;
        Rect[i].x   =   32*i;
        Rect[i].y   =   0;
    }

}
void Player::SetImage()
{
    Surface=loadImage("romfs:/Graphics/Sprites/Player.png");

}
void Player::SetXY(int S_x,int S_y)
{
    x   =   S_x;
    y   =   S_y;
}


//          MOVEMENT        //
void Player::MoveDown()
{

    ANIM_Delay++;
    if(ANIM_Delay >= 1)
    {
        ANIM_Delay=0;
        ANIM_Frames++;
    }
    if(ANIM_Frames>2)ANIM_Frames=0;
}
void Player::MoveLeft()
{
    ANIM_Delay++;
    if(ANIM_Delay >= 1)
    {
        ANIM_Delay=0;
        ANIM_Frames++;
    }
    if(ANIM_Frames<3 || ANIM_Frames > 5)ANIM_Frames=3;
}
void Player::MoveRight()
{
    
    ANIM_Delay++;
    if(ANIM_Delay >= 1)
    {
        ANIM_Delay=0;
        ANIM_Frames++;
    }
    if(ANIM_Frames<6 || ANIM_Frames > 8)ANIM_Frames=6;
    
}
void Player::MoveUp()
{
    
    ANIM_Delay++;

    if(ANIM_Delay >= 1)
    {
        ANIM_Delay=0;
        ANIM_Frames++;
    }
    if(ANIM_Frames<9 || ANIM_Frames > 11)ANIM_Frames=9;
}

void Player::Move()
{
    if(moveLeft)
    {
        MoveLeft();
        lastPos=3;
    }
    if(moveRight)
    {
        MoveRight();
        lastPos=6;
    }
    if(moveUp)
    {
        MoveUp();
        lastPos=9;
    }
    if(moveDown)
    {
        MoveDown();
        lastPos=0;
    }

    if(!moveLeft && !moveRight && !moveUp && !moveDown)
    {
        ANIM_Frames=lastPos;
    }
}
//////////////////////////////////////////////////////

int Player::Attack()
{
    int Damage = rand () % STR;
    return Damage;
}

int Player::Attacked(int DMG)
{
    int Protected = rand() % DEF;
    int Damage = DMG - DEF;
    if(Damage > 0)HP-=Damage;
}

void Player::LevelUp()
{
    LVL++;
    HP+=LVL*15;
}
void Player::Update(SDL_Surface* U_Screen)
{
    Move();
    applySurface(x,y,Surface,U_Screen,&Rect[ANIM_Frames]);
}
