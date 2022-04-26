#include <GameStructure.h>
#include <Player.h>
#include <iostream>

void GameBase::init() {

	//Initialize Environment
	SDL_Log("Initializing Game");

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

	//Load Texture
	SDL_Log("Loading Texture:");
	t->load(renderer);
	menu->load(renderer);

	//Setup Object
	SDL_Log("Setup Object");
	o1.setTexture(menu);
	o1.setSize(2, 2);
	o1.setPos(5, 5);
	o2.setTexture(t);
	
	//Setup Scene
	SDL_Log("Setup Scene");
	s1.push_back((GameObject*)&o1);
	s2.push_back((GameObject*)&o2);

	addScene("scene1", s1);
	addScene("scene2", s2);

	changeScene("scene1");

	SDL_Log("Complete");
}


void GameBase::render(){
	SDL_RenderClear(renderer);

	for (GameObject* a : (scene[presentedscene])) {
		a->render(renderer);
	}

	SDL_RenderPresent(renderer);
}


void GameBase::eventCheck(SDL_Event* Event) {
	if (Event->type == SDL_QUIT) {
		running = false;
		return;
	}

	if (Event->type == SDL_KEYDOWN) {
		switch(Event->key.keysym.sym) {
		case SDLK_b: {
			changeScene(MENU);
			break;
		}
				
		case SDLK_v: {
			changeScene(GAME);
			break;
		}
				
		}
	}

	for (GameObject* a : (scene[presentedscene])) {
		a->eventCheck(Event);
	}
}


void GameBase::tick() {
	for (GameObject* a : (scene[presentedscene])) {
		a->tick();
	}
}


void GameBase::quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	delete t;
	delete menu;
	t = NULL;
	menu = NULL;
}


void GameBase::run() {

	init();

	while (running) {

		while (SDL_PollEvent(&Event)) {
			eventCheck(&Event);
		}

		tick();

		render();

	}

	quit();

}



void GameBase::addScene(std::string name, std::vector<GameObject*> objects) {
	scene.insert(std::pair<std::string, std::vector<GameObject*>>(name, objects));
}

void GameBase::changeScene(std::string name) {
	presentedscene = name;

}





