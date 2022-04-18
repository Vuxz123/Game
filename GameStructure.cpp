#include "GameStructure.h"
#include <Player.h>

void GameStructure::init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if ((window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL)) == NULL) {
		SDL_Log("Unable to create Window: %s", SDL_GetError());
		return;
	}

	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		SDL_Log("Unable to create Renderer: %s", SDL_GetError());
		return;
	}

	Player* player = new Player();

	player->init(renderer);

	player->a();

	((GameObject*)player)->a();

	gameobjects.push_back((GameObject*)player);

	for (GameObject* a : gameobjects) {
		a->a();
	}

}


void GameStructure::render(){
	for (GameObject* a : gameobjects) {
		a->render(renderer);
	}
}


void GameStructure::eventCheck(SDL_Event* Event) {
	if (Event->type == SDL_QUIT) {
		running = false;
		return;
	}
	int i = 0;

	for (GameObject* a : gameobjects) {
		i++;
		if (a == NULL) {
			SDL_Log("%d", i);
		}
		a->eventCheck(Event);
	}
}


void GameStructure::tick() {
	for (GameObject* a : gameobjects) {
		a->tick();
	}
}


void GameStructure::quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	for (GameObject* a : gameobjects) {
		a->free();
		delete a;
		a = NULL;
	}
}


void GameStructure::run() {

	init();

	while (running) {
		render();

		while (SDL_PollEvent(&Event)) {
			eventCheck(&Event);
		}

		tick();

	}

	quit();

}









