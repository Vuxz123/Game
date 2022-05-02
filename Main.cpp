#include <GameStructure.h>

static GameBase* game;

int main(int argc, char* argv[]) {
	game = new GameBase();

	game->run();

	delete game;

	game = NULL;

	return 1;
}

static GameBase* getGame() {
	return game;
}

