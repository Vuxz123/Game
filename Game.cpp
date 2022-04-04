#include <SDL.h>
#include <SDL_image.h>
#include <Player.cpp>
#include <vector>
#include <Util.cpp>
#include <RB.cpp>

#pragma once
class CApp {
private:
    bool Running;

    SDL_Surface* Surf_Display;
    SDL_Window* Window;
    SDL_Renderer* Renderer;

    std::vector<Renderable*> renderarray;

    Player player;

public:
    CApp() {
        Window = NULL;
        Surf_Display = NULL;
        Running = true;
    }

    int OnExecute() {
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

    bool OnInit() {
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

        player = Player(Renderer, Window);

        renderarray.push_back(&player);

        return true;
    }

    void OnEvent(SDL_Event* Event){

        if (Event->type == SDL_QUIT) {
            Running = false;
        }



    }

    void OnLoop() {
    }

    void OnRender() {
        if (!renderarray.empty()) {
            for (auto rendered : renderarray) {
                rendered->render(Renderer);
            }
        }
        Util::presentScene(Renderer);
    }

    void OnCleanup() {
        SDL_DestroyWindow(Window);
        SDL_DestroyRenderer(Renderer);
        Window = NULL;
        Renderer = NULL;
        SDL_Quit();
    }
};

