#pragma once
#include "GameObject.h"
#include <functional>

class AbOb :
    public GameObject
{
private:
	std::function<void(SDL_Event* Event)> actionevent;
	std::function<void()> actiontick;

public:

	AbOb(){
		actionevent = [=](SDL_Event* Event) {
			return;
		};
		actiontick = [=]() {
			return;
		};
	}

	void setEvent(std::function<void(SDL_Event* Event)> _actionevent) {
		actionevent = _actionevent;
	}

	void setTick(std::function<void()> _actiontick) {
		actiontick = _actiontick;
	}

	void init(SDL_Renderer* renderer) override{}

	void render(SDL_Renderer* renderer) override{}

	void eventCheck(SDL_Event* Event) override{
		actionevent(Event);
	}

	void tick() override{
		actiontick();
	}

	void free() override{}
};

