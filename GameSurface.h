#include <SDL.h>
#pragma once
class GameSurface
{
public:
    GameSurface();

public:
    static SDL_Surface* OnLoad(char* File);

    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
};

