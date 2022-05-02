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
		switch (Event->key.keysym.scancode)
		{
		case SDL_SCANCODE_A: {
			position = position + Vector2D(-30, 0);
			break;
		}
		case SDL_SCANCODE_D: {
			position = position + Vector2D(30, 0);
			break;
		}
		default: {
			break;
		}
		}
		
		switch (Event->key.keysym.scancode){
		case SDL_SCANCODE_W: {
			position = position + Vector2D(0, -30);
			break;
		}
		case SDL_SCANCODE_S: {
			position = position + Vector2D(0, 30); 
			break;
		}
		default: {
			break;
		}
			
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