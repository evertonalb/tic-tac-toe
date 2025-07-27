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

	background = IMG_LoadTexture(renderer, "../assets/board.png");
	if (!background){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		throw std::runtime_error("Failed to load background texture: " + std::string(SDL_GetError()));
	}
	SDL_SetTextureScaleMode(background, SDL_SCALEMODE_NEAREST);
	
	circle = new Mark("../assets/circle.png", renderer, {0, 0, 35, 35}, 39);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	float scale = (float) h / background->h;
	
	// Setting up grid matrix
	SDL_FRect cell;
	
	cell.w = scale * 35;
	cell.h = scale * 35;
	cell.y = scale * 8;
	
	int stride = scale * 39;
	
	for (int i = 0; i < 3; i++){
		cell.x = scale * 8;
		for (int j = 0; j < 3; j++){
			grid[i][j] = cell;
			cell.x += stride;
		}
		cell.y += stride;
	}

}

void Game::loop(){
	poll_events();
	update();
	draw();
}

void Game::poll_events(){
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type){
		case SDL_EVENT_QUIT:
			running = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			on_key_press(event.key);
			break;
		default:
			break;
		}
	}
}

void Game::on_key_press(const SDL_KeyboardEvent &key){
	switch (key.key){
	case SDLK_ESCAPE:
		running = false;
		break;
	default:
		break;
	}
}

void Game::update(){
	// TODO: Update game state
}

void Game::draw(){
	SDL_SetRenderDrawColor(renderer, 238, 195, 154, 255);
	SDL_RenderClear(renderer);
	
	// Draw board
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_FRect target = {(float) w - h, 0, (float) h, (float) h};
	SDL_RenderTexture(renderer, background, NULL, &target);
	
	
	// Draw circles and crosses here
	SDL_FRect srcrect = {0, 0, 35, 35};
	SDL_RenderTexture(renderer, circle->sprite, &circle->srcrect, &grid[2][1]);

	SDL_RenderPresent(renderer);
}
