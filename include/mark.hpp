#ifndef MARK_HPP
#define MARK_HPP

#include <SDL3/SDL.h>

class Mark {
private:
	SDL_FRect start; // FRect for the first sprite
	int stride; // Step between consecutive sprites
public:
	SDL_Texture *sprite;
	SDL_FRect srcrect; // Current source FRect
	Mark(const char *file, SDL_Renderer *renderer, SDL_FRect start, int stride);
	~Mark();
};

#endif // MARK_HPP