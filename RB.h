#pragma once
#include <SDL.h>
#include <iostream>
class Renderable{
public:
	virtual void render(SDL_Renderer* renderer) = 0;
};
