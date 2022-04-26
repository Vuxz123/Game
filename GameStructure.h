#pragma once
#include <vector>
#include <GameObject.h>
#include <string>
#include <map>
#include <Player.h>
#include <TexOb.h>
class GameBase
{
private:
	const std::string MENU = "scene1";
	const std::string GAME = "scene2";

	TexOb o1 = TexOb();
	Player o2 = Player(renderer);
	std::vector<GameObject*> s1, s2;

	Texture* t = new Texture("Player.bmp");
	Texture* menu = new Texture("GameMenu.png");

	
private:
	bool running = true;

	std::map<std::string, std::vector<GameObject*>> scene;
	std::string presentedscene;

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event Event;

	const std::string TITLE = "Hang Man - 0.0.1";

public:
	void addScene(std::string name, std::vector<GameObject*> objects);

	void changeScene(std::string name);

	GameBase(){}

	void init();

	void render();

	void eventCheck(SDL_Event* Event);

	void tick();

	void quit();

	void run();

	~GameBase() {
		quit();
	}
};

