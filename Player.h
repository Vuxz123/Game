#pragma once
#include <GameObject.h>

class Player : GameObject
{
public:

	Player(SDL_Renderer* renderer);

	void init(SDL_Renderer* renderer) override;

	void render(SDL_Renderer* renderer) override;
	
	void eventCheck(SDL_Event* Event) override;

	void tick() override;

	void free() override;

	std::string getName() override {
		return NAME;
	}

	void setTexture(Texture* a) override {
		texture = a;
	}

	void a() override;

	~Player();
};

