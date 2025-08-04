#include "game.hpp"
#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>

void Game::reset_game(){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			occupied[i][j] = false;
			marks[i * 3 + j] = {Mark(), -1};
		}
	}
	currentI = currentJ = 0;
	currentMark = (SDL_rand(2) == 0) ? circle : cross;
	playerWon = false;
	askReplay = false;
	
	delete text;
	text = new Text("../assets/ByteBounce.ttf", 70, renderer);
}

Game::Game(int w, int h, const char *title)
{
	window = SDL_CreateWindow(title, w, h, SDL_WINDOW_MAXIMIZED);
	if (!window) {
		throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
	}
	
	SDL_Surface *icon = IMG_Load("../assets/icon.png");
	if (!icon){
		SDL_DestroyWindow(window);
		throw std::runtime_error("Failed to load icon: " + std::string(SDL_GetError()));
	}
	
	SDL_SetWindowIcon(window, icon);
	SDL_DestroySurface(icon);

	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_DestroyWindow(window);
		throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
	}
	
	marks.resize(9); // Preallocate space for 9 marks
	
	text = new Text("../assets/ByteBounce.ttf", 70, renderer);
}

Game::~Game(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete circle;
	delete cross;
	delete text;
	TTF_Quit();
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
	
	circle = new Mark(CIRCLE, "../assets/circle.png", renderer, {0, 0, 35, 35}, 35);
	cross = new Mark(CROSS, "../assets/cross.png", renderer, {0, 0, 35, 35}, 35);
	if (!circle || !cross) {
		SDL_DestroyTexture(background);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		throw std::runtime_error("Failed to create marks: " + std::string(SDL_GetError()));
	}
	currentMark = (SDL_rand(2) == 0) ? circle : cross;

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	scale = (float) h / background->h;
	
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
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			on_click(event.button);
			break;
		case SDL_EVENT_MOUSE_MOTION:
			{
				int cell = get_cell_from_position(event.motion.x, event.motion.y);
				if (cell == -1) break;
				currentI = cell / 3;
				currentJ = cell % 3;
			}
			break;
		case EVENT_WIN:
			playerWon = true;
			break;
		case EVENT_ASK_REPLAY:
			askReplay = true;
			playerWon = false;
			break;
		default:
			break;
		}
	}
}

void Game::on_key_press(const SDL_KeyboardEvent &key){
	switch (key.key){
	case SDLK_R:
		if (!askReplay) break; // Only reset if replay is asked
		reset_game();
		break;
	case SDLK_ESCAPE:
		running = false;
		break;
	default:
		break;
	}
}

void Game::on_click(const SDL_MouseButtonEvent &button){
	int cell = -1;
	switch (button.button){
	case SDL_BUTTON_LEFT:
		if (playerWon || askReplay) break; // Ignore clicks if game over or asking for replay
		
		cell = get_cell_from_position(button.x, button.y);

		if (cell != -1){
			int i = cell / 3;
			int j = cell % 3;
			if (occupied[i][j]) break; // Cell already occupied
			
			marks[cell] = {*currentMark, cell};
			occupied[i][j] = true;
			currentMark->randomize_sprite();
			currentMark = (currentMark == circle) ? cross : circle;

			MarkType winner = check_winner();
			if (winner != NONE) {
				SDL_Event winEvent;
				winEvent.type = EVENT_WIN;
				SDL_PushEvent(&winEvent);
			}
		}
		break;
	
	default:
		break;
	}
}

MarkType Game::check_winner(){
	// Rows
	for (int i = 0; i < 3; i++) {
		if (occupied[i][0] && occupied[i][1] && occupied[i][2]) {
			if (marks[i * 3].first.type == marks[i * 3 + 1].first.type && 
				marks[i * 3].first.type == marks[i * 3 + 2].first.type) {
				return marks[i * 3].first.type;
			}
		}
	}
	
	// Columns
	for (int j = 0; j < 3; j++) {
		if (occupied[0][j] && occupied[1][j] && occupied[2][j]) {
			if (marks[j].first.type == marks[j + 3].first.type && 
				marks[j].first.type == marks[j + 6].first.type) {
				return marks[j].first.type;
			}
		}
	}

	// Main diagonal
	if (occupied[0][0] && occupied[1][1] && occupied[2][2]) {
		if (marks[0].first.type == marks[4].first.type && 
			marks[0].first.type == marks[8].first.type) {
			return marks[0].first.type;
		}
	}
	
	// Antidiagonal
	if (occupied[0][2] && occupied[1][1] && occupied[2][0]) {
		if (marks[2].first.type == marks[4].first.type && 
			marks[2].first.type == marks[6].first.type) {
			return marks[2].first.type;
		}
	}
	
	return NONE;
}

int Game::get_cell_from_position(float x, float y) const {
	int ans;
	if (x > 8 * scale && x < 42 * scale) ans = 0;
	else if (x > 47 * scale && x < 81 * scale) ans = 1;
	else if (x > 86 * scale && x < 120 * scale) ans = 2;
	else return -1;

	if (y > 8 * scale && y < 42 * scale) ans += 0;
	else if (y > 47 * scale && y < 81 * scale) ans += 3;
	else if (y > 86 * scale && y < 120 * scale) ans += 6;
	else return -1;

	return ans;
}

void Game::update(){
	static SDL_Time lastTime = SDL_GetTicks();
	SDL_Time currentTime = SDL_GetTicks();
	SDL_Time delta = currentTime - lastTime;
	
	if (delta < 16) return; // Limit to ~60 FPS
	
	static SDL_Time gameOverTimer = 1500; // in milliseconds
	if (playerWon){
		// Start game over timer	
		gameOverTimer -= delta;
		
		if (gameOverTimer <= 0){ // When the timer is up
			SDL_Event ask;
			ask.type = EVENT_ASK_REPLAY;
			SDL_PushEvent(&ask);
			gameOverTimer = 1500; // Reset timer
			return;
		}
	}
	
	lastTime = currentTime;
}

void Game::draw(){
	SDL_SetRenderDrawColor(renderer, 238, 195, 154, 255);
	SDL_RenderClear(renderer);
	
	// Draw board
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_FRect target = {(float) w - h, 0, (float) h, (float) h};
	SDL_RenderTexture(renderer, background, NULL, &target);
	
	// Draw marks
	if (!occupied[currentI][currentJ]) {
		currentMark->set_transparency(128);
		currentMark->render_mark(renderer, grid[currentI][currentJ]);
		currentMark->set_transparency(255);
	} 
	
	for (auto& mark : marks) {
		if (mark.first.type == NONE) continue; // Skip empty marks
		mark.first.render_mark(renderer, grid[mark.second / 3][mark.second % 3]);
	}
	
	if (playerWon) text->render((currentMark->type == CIRCLE) ? "Crosses win!" : "Circles win!", 5, 15);
	if (askReplay) text->render("Press R to replay\nor ESC to quit", 5, 15);
	
	SDL_RenderPresent(renderer);
}
