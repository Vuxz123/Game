#pragma once
#include <SDL.h>
#include <string>

const float qd = 1; // 10 pixel 1 cm;

inline SDL_Rect toSDL_Rect(Vector2D position, int w, int h) {
	SDL_Rect a;
	a.x = (int)position.getX() * qd;
	a.y = (int)position.getY() * qd;
	a.w = w;
	a.h = h;
	return a;
}