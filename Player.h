#pragma once
#include <SDL.h>
#include <RB.h>
#include <Vector2D.h>
#include <string>
#include <Util.h>
#include <GameTextureManager.h>

class Player : public Renderable
{
private:
	std::string link = "Player.bmp";
	Vector2D pos;
	SDL_Texture* texture;

public:

	Player(){}

	Player(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer) override {
		Pos p = Util::fromVectortoPos(pos);
		GameTextureManager::blit(renderer, texture, p.x, p.y);
	}

	void move(Vector2D v);

};

