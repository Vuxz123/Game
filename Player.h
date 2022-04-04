#pragma once
#include <SDL.h>
#include <RB.h>
#include <Vector2D.h>
#include <string>
#include <Util.h>
#include <Texture.h>

class Player : public Renderable
{
private:
	std::string link = "Player.bmp";
	Vector2D pos;
	LTexture texture;

public:

	Player(){}

	Player(SDL_Renderer* Renderer, SDL_Window* Window) {
		if (!texture.loadFromFile(link, Window, Renderer)) {
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Fail to load Player texture");
		}
		pos = Vector2D(0, 0);
	}

	void render(SDL_Renderer* Renderer) override {
		Pos p = Util::fromVectortoPos(pos);
		SDL_RenderSetScale(Renderer, 0.4, 0.4);
		texture.render(p.x, p.y, Renderer);
		SDL_RenderSetScale(Renderer, 1, 1);
	}

	void move(Vector2D v) {
		this->pos = this->pos + v;
	}

};

