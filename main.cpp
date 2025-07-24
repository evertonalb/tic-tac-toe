#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <stdexcept>
#include "game.hpp"

int SDL_main(int argc, char* argv[]) {
	Game game(768, 768, "Tic Tac Toe");

	try {
		game.init();
	} catch (const std::exception& e) {
		SDL_Log("Error initializing game: %s", e.what());
		return -1;
	}
	
	while (game.running) {
		game.loop();
		SDL_Delay(16); // Simulate frame delay
	}

	SDL_Quit();
	
	return 0;
}