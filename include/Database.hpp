#include "main.hpp"

#include "Map.hpp"
#include "Npc.hpp"
#include "Player.hpp"

#ifndef DATABASE_H
#define DATABASE_H


//      NPC     //
#define NPC_SLIME   0
////////////////////////////////////////////////////////////

//      BattleBacks //
#define BB_DEMOFORREST  0


npc Slime("Slime",32,32,5);
Player P_Player;


void Data_loadPlayer()
{
    P_Player.ANIM_Frames=0;
    P_Player.lastPos=0;
    P_Player.SetImage();
    P_Player.SetXY(241,183);
    P_Player.moveLeft=true;
}
void Data_loadNpc()
{
    Slime.SetImage("romfs:/Graphics/Sprites/Slime.png");
    Slime.SetATTR(25,0,3,3);
};
void unloadNpc(npc l_npc);
#endif