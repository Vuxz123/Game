#include <SDL.h>
#include "Player.h"
#include <vector>
#include <utility>
#pragma once
class CApp {
private:
    bool    Running;

    SDL_Surface* Surf_Display;
    SDL_Window* Window;
    SDL_Renderer* Renderer;

    std::vector<Renderable*> renderarray;

    Player player;

public:
    CApp();

    int OnExecute();

public:

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();
};

