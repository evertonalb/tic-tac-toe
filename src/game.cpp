#include "game.hpp"
#include <stdexcept>

Game::Game(int w, int h, const char* title){
	window = SDL_CreateWindow(title, w, h, SDL_WINDOW_MAXIMIZED);
	if (!window) {
		throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_DestroyWindow(window);
		throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
	}
}

Game::~Game(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::init(){
	running = true;
}
