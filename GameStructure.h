#pragma once
#include <vector>
#include <GameObject.h>
#include <string>
#include <map>
#include <Player.h>
#include <TexOb.h>
#include <ButtonList.h>
#include <AbOb.h>
class GameBase
{
public:
	const std::string MENU = "scene1";
	const std::string GAME = "scene2";
	const std::string IGMENU = "scene3";

	std::vector<GameObject*> s1, s2, s3;

	TexOb mo = TexOb(), mbo = TexOb(), pbo = TexOb() , pbo2 = TexOb();
	ButtonList mbl = ButtonList();
	Player o2 = Player(renderer);
	AbOb ao = AbOb();

	Texture* t = new Texture("Player.bmp");
	Texture* menu = new Texture("GameMenu.png"); //256 x 128
	Texture* mb = new Texture("GameMenuBackGroud.png"); //600 x 600
	Texture* pb = new Texture("PlayButton.png"); //100 x 50
	Texture* pb2 = new Texture("PlayButton.png"); //100 x 50

	
private:
	bool running = true;

	std::map<std::string, std::vector<GameObject*>> scene;
	std::string presentedscene;

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event Event;

	const std::string VERSION = "0.0.6";
	const std::string TITLE = "Hang Man";

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

