#ifndef GAME_HPP
#define GAME_HPP

#include <SDL3/SDL.h>

class Game{
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	bool running = false;
	Game(int w, int h, const char* title);
	~Game();
	void init();
};


#endif // GAME_HPP