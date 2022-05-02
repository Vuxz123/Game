#include <GameStructure.h>
#include <Player.h>
#include <iostream>

void GameBase::init() {

	//test
	/*int w, h;
	SDL_GetWindowSize(window, &w, &h);
	std::cout << mb->getWidth() << " " << mb->getHeight() << std::endl << w << " " << h << std::endl;*/


	//Initialize Environment
	SDL_Log("Initializing Game");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if ((window = SDL_CreateWindow((TITLE + " - " + VERSION).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL)) == NULL) {
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
	mb->load(renderer);
	pb->load(renderer);
	pb2->load(renderer);

	//Setup Object
	SDL_Log("Setup Object");
	mbo.setTexture(mb);
	mbo.setSize(1, 1);
	mbo.setPos(0, 0);

	mo.setTexture(menu);
	mo.setSize(1.5, 1.5);
	mo.setPos(30, 30);

	pbo.setTexture(pb);
	pbo.setSize(1.5, 1.5);
	pbo.setPos(30, 30 + 128 + 30 );

	pbo2.setTexture(pb2);
	pbo2.setSize(1.5, 1.5);
	pbo2.setPos(30, 30 + 128 + 30 + 50 + 30);

	//std::cout << (pb2 == pb) << std::endl;

	mbl.addButton(&pbo, [=]() {
		changeScene(GAME);
		return;
		}, 0);

	mbl.addButton(&pbo2, []() {
		std::cout << "2";
		return;
		}, 1);

	o2.setTexture(t);

	ao.setEvent([=](SDL_Event* Event) {
		if (Event->type == SDL_KEYDOWN && Event->key.keysym.sym == SDLK_ESCAPE) {
			changeScene(MENU);
		}
		return;
		});
	
	//Setup Scene
	SDL_Log("Setup Scene");
	s1.push_back((GameObject*)&mbo);
	s1.push_back((GameObject*)&mo);
	s1.push_back((GameObject*)&mbl);

	s2.push_back((GameObject*)&o2);
	s2.push_back((GameObject*)&ao);

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
	delete mb;
	delete pb;
	delete pb2;
	t = NULL;
	menu = NULL;
	mb = NULL;
	pb = NULL;
	pb2 = NULL;
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





