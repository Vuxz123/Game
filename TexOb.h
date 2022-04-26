#pragma once
#include <GameObject.h>
class TexOb : GameObject
{
private:
	float sizex,sizey;

public:
	TexOb(){}

	void setPos(float x, float y);

	void setSize(float x, float y);

	void init(SDL_Renderer* renderer) override;

	void render(SDL_Renderer* renderer) override;

	void eventCheck(SDL_Event* Event) override;

	void tick() override;

	void free() override;

	void setTexture(Texture* a) override;

	~TexOb();
};

