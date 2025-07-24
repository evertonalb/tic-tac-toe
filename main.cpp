#include <SDL3/SDL_main.h>
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
	
	return 0;
}