#include "Player.h"
#include <Util.h>

void Player::init(SDL_Renderer* renderer) {
	PATH = "Player.bmp";
	position = Vector2D(0, 0);

	texture = Texture(PATH);

	texture.load(renderer);
}



void Player::render(SDL_Renderer* renderer) {

}

void Player::eventCheck(SDL_Event* Event) {

}

void Player::tick() {

}

void Player::a() {
	SDL_Log("a");
}

void Player::free() {
	texture.free();
}