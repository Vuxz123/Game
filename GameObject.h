#pragma once
#include <SDL.h>
#include <string>
#include <Vector2D.h>
#include <Texture.h>


class Animator {

};

class GameObject {

protected:
	std::string PATH;
	
	Texture texture;

	Vector2D position;
	
public:
	GameObject(){}

	virtual void init(SDL_Renderer* renderer) = 0;

	virtual void render(SDL_Renderer* renderer) = 0;

	virtual void eventCheck(SDL_Event* Event) = 0;

	virtual void tick() = 0;

	virtual void free() = 0;

	virtual void a();

};

