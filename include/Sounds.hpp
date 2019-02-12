#include "main.hpp"
#ifndef SOUNDS_H
#define SOUNDS_H

Mix_Chunk *CursorSelect;
Mix_Chunk *CursorSelected;

Mix_Music *Music;


//FX
#define FX_SELECT  0
#define FX_SELECTED  1

//MUSIC
#define MUS_ANOTHERCASTLE 0


void SoundInit()
{
    CursorSelect=Mix_LoadWAV("romfs:/Sounds/Select.wav");
    CursorSelected=Mix_LoadWAV("romfs:/Sounds/Selected.wav");
}

void PlaySound(int chunkint)
{
    switch(chunkint)
    {
        case FX_SELECT:
            Mix_PlayChannel(-1,CursorSelect,0);
            break;
        case FX_SELECTED:
            Mix_PlayChannel(-1,CursorSelected,0);
            break;
        default:
            break;
    }
}

void ClearAllSounds()
{
    Mix_FreeChunk(CursorSelect);
}


void LoadSong(int L_Mus)
{
    switch (L_Mus)
    {
        case MUS_ANOTHERCASTLE: 
            Music=Mix_LoadMUS("romfs:/Music/AnotherCastle.wav");
            break;
    
        default:
            break;
    }
}
void PlaySong()
{
    Mix_PlayMusic(Music,-1);
}
void UnloadSong()
{
    Mix_FreeMusic(Music);
}

#endif