#ifndef GAME_HPP
#define GAME_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Game{
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
public:
	bool running = false;
	Game(int w, int h, const char* title);
	~Game();
	void init();
	void loop();
	void poll_events();
	void on_key_press(const SDL_KeyboardEvent& key);
	void update();
	void draw();
};


#endif // GAME_HPP