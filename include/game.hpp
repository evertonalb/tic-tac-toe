#ifndef GAME_HPP
#define GAME_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "mark.hpp"
#include <vector>
#include "text.hpp"

// Custom events
#define EVENT_WIN SDL_EVENT_USER
#define EVENT_ASK_REPLAY SDL_EVENT_USER + 1

class Game {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	SDL_FRect grid[3][3];
	bool occupied[3][3] = {{false, false, false}, {false, false, false}, {false, false, false}};
	float scale;
	int currentI = 0, currentJ = 0;
	Mark *circle, *cross, *currentMark;
	std::vector< std::pair<Mark, int> > marks;
	bool playerWon = false;
	bool askReplay = false;
	Text *text = NULL;

	void reset_game();
public:
	bool running = false;
	Game(int w, int h, const char* title);
	~Game();
	void init();
	void loop();
	void poll_events();
	void on_key_press(const SDL_KeyboardEvent& key);
	void on_click(const SDL_MouseButtonEvent& button);
	MarkType check_winner();
	int get_cell_from_position(float x, float y) const;
	void update();
	void draw();
};


#endif // GAME_HPP