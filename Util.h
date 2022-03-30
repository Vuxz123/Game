#pragma once
#include <Vector2D.h>
struct Pos {
	long x, y;
};


class Util
{
public:
	static const int n = 10;//n pixel = 1 m

	static Pos fromVectortoPos(Vector2D v) {
		Pos p;
		p.x = (long)v.getX() * Util::n;
		p.y = (long)v.getY() * Util::n;
		return p;
	}

	static void prepareScene(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
		SDL_RenderClear(renderer);
	}

	static void presentScene(SDL_Renderer* renderer)
	{
		SDL_RenderPresent(renderer);
	}
};


