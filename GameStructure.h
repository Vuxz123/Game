#pragma once
#include <vector>
#include <GameObject.h>
#include <string>
class GameStructure
{
private:
	bool running = true;

	std::vector<GameObject*> gameobjects;

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event Event;

	const std::string TITLE = "Hang Man - 0.0.1";

public:
	void init();

	void render();

	void eventCheck(SDL_Event* Event);

	void tick();

	void quit();

	void run();

};

