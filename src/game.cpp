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

void Game::loop(){
	poll_events();
	update();
	draw();
}

void Game::poll_events(){
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT){
			running = false;
		}
	}
}

void Game::update(){
	// TODO: Update game state
}

void Game::draw(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	// TODO: Drawing logic

	SDL_RenderPresent(renderer);
}
