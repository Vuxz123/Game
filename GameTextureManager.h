#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
class GameTextureManager
{
private:
	static std::map<std::string, SDL_Texture*> TextureStorage;

public:
	static SDL_Texture* loadTexture(std::string name, SDL_Renderer* renderer);

	static void blit(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

};



