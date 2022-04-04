#pragma once
#include <SDL.h>
#include <iostream>
#include <Game.h>
class Renderable{
public:
	virtual void render(SDL_Renderer* renderer = CApp::Renderer) = 0;
};
