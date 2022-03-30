#include "GameTextureManager.h"

SDL_Texture* GameTextureManager::loadTexture(std::string name, SDL_Renderer* renderer)
{
	SDL_Texture* texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", name.c_str());

	texture = IMG_LoadTexture(renderer, name.c_str());

	return texture;
}
void GameTextureManager::blit(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}