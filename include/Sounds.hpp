#include "main.hpp"
#ifndef SOUNDS_H
#define SOUNDS_H

Mix_Chunk *CursorSelect;
Mix_Chunk *CursorSelected;

#define SELECT_WAV  0
#define SELECTED_WAV  1
void SoundInit()
{
    CursorSelect=Mix_LoadWAV("romfs:/Sounds/Select.wav");
    CursorSelected=Mix_LoadWAV("romfs:/Sounds/Selected.wav");
}
void PlaySound(int chunkint)
{
    switch(chunkint)
    {
        case SELECT_WAV:
            Mix_PlayChannel(-1,CursorSelect,0);
            break;
        case SELECTED_WAV:
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

#endif