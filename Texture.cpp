#include "Texture.h"

void Texture::load(SDL_Renderer* renderer) {
	SDL_Surface* sur = IMG_Load(PATH.c_str());

	w = sur->w;
	h = sur->h;

	texture = SDL_CreateTextureFromSurface(renderer, sur);

	SDL_FreeSurface(sur);
	sur = NULL;
}