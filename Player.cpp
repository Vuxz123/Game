#include "Player.h"
#include "GameTextureManager.h"
#include <Util.h>

Player::Player(SDL_Renderer* renderer) {

	texture = GameTextureManager::loadTexture( link, renderer);
	if (texture == NULL) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Fail to load Player texture");
	}
	pos = Vector2D(0, 0);
}

void Player::move(Vector2D v) {
	this->pos = this->pos + v;
}