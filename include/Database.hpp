#include "main.hpp"

#include "Map.hpp"
#include "Npc.hpp"
#include "Player.hpp"

#ifndef DATABASE_H
#define DATABASE_H


#define NPC_SLIME   0



npc Slime("Slime",32,32,5);
Player DemoPlayer;


void Data_loadPlayer()
{
    DemoPlayer.ANIM_Frames=0;
    DemoPlayer.lastPos=0;
    DemoPlayer.SetImage();
}
void Data_loadNpc()
{
    Slime.SetImage("romfs:/Graphics/Sprites/Slime.png");
    Slime.SetATTR(25,0,5,5);
};
void unloadNpc(npc l_npc);
#endif