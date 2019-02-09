#include "main.hpp"

#include "Map.hpp"
#include "Npc.hpp"

#ifndef DATABASE_H
#define DATABASE_H


#define NPC_SLIME   0



npc Slime("Slime",32,32,5);
npc SlimePlayer("Player",32,32,5);

void loadNpc()
{
    Slime.SetImage("romfs:/Graphics/Sprites/Slime.png");
    Slime.SetATTR(25,0,5,5);

    SlimePlayer.SetImage("romfs:/Graphics/Sprites/I_Slime.png");
    SlimePlayer.SetATTR(25,0,5,5);
};
void unloadNpc(npc l_npc);
#endif