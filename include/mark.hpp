#ifndef MARK_HPP
#define MARK_HPP

#include <SDL3/SDL.h>

class Mark {
private:
	SDL_FRect start; // FRect for the first sprite
	int stride; // Step between consecutive sprites
public:
	SDL_Surface *sprite = NULL;
	SDL_Texture *texture = NULL; // Texture for rendering
	SDL_FRect srcrect; // Current source FRect
	Mark(const char *file, SDL_Renderer *renderer, SDL_FRect start, int stride);
	void randomize_sprite();
	void render_mark(SDL_Renderer *renderer, SDL_FRect &target);
	~Mark();
};

#endif // MARK_HPP