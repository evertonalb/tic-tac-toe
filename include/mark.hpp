#ifndef MARK_HPP
#define MARK_HPP

#include <SDL3/SDL.h>

typedef enum MarkType {
	CIRCLE,
	CROSS,
	NONE
} MarkType;

class Mark {
private:
	SDL_FRect start; // FRect for the first sprite
	int stride; // Step between consecutive sprites
public:
	MarkType type;
	SDL_Surface *sprite = NULL;
	SDL_Texture *texture = NULL; // Texture for rendering
	SDL_FRect srcrect; // Current source FRect
	Mark();
	Mark(const Mark&  other);
	Mark(MarkType type, const char *file, SDL_Renderer *renderer, SDL_FRect start, int stride);
	Mark& operator=(const Mark&);
	void randomize_sprite();
	void render_mark(SDL_Renderer *renderer, SDL_FRect &target);
	~Mark();
};

#endif // MARK_HPP