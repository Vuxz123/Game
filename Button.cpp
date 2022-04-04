#include <SDL.h>
#include <RB.h>
#include <Vector2D.h>
#include <Game.h>

class Button : Renderable {
private:
	std::string link = "Player.bmp";
	Vector2D pos;
	LTexture texture;
	int w, h;
public:
	Button(SDL_Renderer* Renderer, SDL_Window* Window) {
		if (texture.loadFromFile(link, Window, Renderer)) {
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Fail to load Player texture");
		}
		pos = Vector2D(0, 0);
	}
	void render(SDL_Renderer* Renderer) {
		Pos p = Util::fromVectortoPos(pos);
		SDL_RenderSetScale(Renderer, 0.4, 0.4);
		texture.render(p.x, p.y, Renderer);
		SDL_RenderSetScale(Renderer, 1, 1);
	}
};