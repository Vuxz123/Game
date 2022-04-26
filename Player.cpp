#include "Player.h"
#include <Util.h>
#include <iostream>

Player::Player(SDL_Renderer* renderer) {
	NAME = "Player";
	PATH = "Player.bmp";
	CLASS = "Player";

	init(renderer);
}

void Player::init(SDL_Renderer* renderer) {
	
	position = Vector2D(0, 0);

}



void Player::render(SDL_Renderer* renderer) {
	SDL_Rect pos = toSDL_Rect(position, texture->getWidth(), texture->getHeight());
	SDL_RenderCopy(renderer, texture->getTexture(), NULL, &pos);
}

void Player::eventCheck(SDL_Event* Event) {
	if (Event->type == SDL_KEYDOWN) {
		switch (Event->key.keysym.sym)
		{
		case SDLK_a: {
			position = position + Vector2D(-3, 0);
			std::cout << "a";
		}
		case SDLK_d: {
			position = position + Vector2D(3, 0);
		}
		case SDLK_w: {
			position = position + Vector2D(0, -3);
		}
		case SDLK_s: {
			position = position + Vector2D(0, 3);
		}
		default:
			break;
		}
		
	}
}

void Player::tick() {

}

void Player::a() {
	SDL_Log("a");
}

void Player::free() {
}

Player::~Player() {
	free();
}