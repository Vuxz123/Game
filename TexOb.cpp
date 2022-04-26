#include "TexOb.h"
#include <Util.h>
void TexOb::setPos(float x, float y) {
	position = Vector2D(x, y);
}

void TexOb::setSize(float x, float y) {
	sizex = x; sizey = y;
}

void TexOb::setTexture(Texture* a) {
	texture = a;
}

void TexOb::init(SDL_Renderer* renderer) {

}

void TexOb::render(SDL_Renderer* renderer) {
	SDL_RenderSetScale(renderer, sizex, sizey);
	SDL_Rect pos = toSDL_Rect(position, texture->getWidth(), texture->getHeight());
	SDL_RenderCopy(renderer, texture->getTexture(), NULL, &pos);
	SDL_RenderSetScale(renderer, 1, 1);
}

void TexOb::eventCheck(SDL_Event* Event) {

}

void TexOb::tick() {

}

void TexOb::free() {

}

TexOb::~TexOb()
{
	free();
}