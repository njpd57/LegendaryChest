#include "main.hpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:
        Player();
        void SetImage();
        void SetXY(int S_x,int S_y);
        void BattleMode();

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void Move();

        int Attack();
        int Attacked(int DMG);
        void LevelUp();

        void BattleAnim(bool Left);
        void Update(SDL_Surface* U_Screen);


        //INPUT

        bool moveLeft;
        bool moveRight;
        bool moveUp;
        bool moveDown;
        int lastPos;
        //ANIMATION
        int ANIM_Frames;
        int ANIM_Delay;
        
    private:
        //STATS
        std::string Name;

        int LVL;   //NIVEL
        int HP;     //VIDA
        int MP;     //MAGIA PARA HABILIDADES
        int STR;    // FUERZA PARA DAÑO
        int DEF;    // Defensa
        bool Alive;



        //POS
        int x;
        int y;

        //IMAGE
        SDL_Surface* Surface;
        SDL_Rect     Rect[11];
        int          IMG_Frames;

        
};  

#endif