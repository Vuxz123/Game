#include<SDL.h>
#include <Windows.h>
#include "Game.h"
#include "Player.h"

float a = 0.1;

bool CApp::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    Window = SDL_CreateWindow("Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024, 768,
        SDL_WINDOW_RESIZABLE);
    if (Window == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Window could not be created! SDL Error: %s\n", SDL_GetError());
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if (Renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }


    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
    

    renderarray = std::vector<Renderable*>();

    player = Player(Renderer);

    renderarray.push_back(&player);

    return true;
}
void CApp::OnEvent(SDL_Event* Event) {
    
    if(Event->type == SDL_QUIT) {
        Running = false;
    }



}

void CApp::OnLoop() {
}
void CApp::OnRender() {
    if (!renderarray.empty()) {
        for (auto rendered : renderarray) {
            rendered->render(Renderer);
        }
    }
    Util::presentScene(Renderer);
}
void CApp::OnCleanup() {
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}

CApp::CApp() {
    Window = NULL;
    Surf_Display = NULL;
    Running = true;
}

int CApp::OnExecute() {
    if (OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while (Running) {
        Util::prepareScene(Renderer);

        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}
