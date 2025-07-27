#include "mark.hpp"

#include <SDL3_image/SDL_image.h>
#include <stdexcept>

Mark::Mark(const char *file, SDL_Renderer *renderer, SDL_FRect start, int stride) : start(start), srcrect(start) {
	sprite = IMG_LoadTexture(renderer, file);
	if (!sprite){
		throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
	}
	SDL_SetTextureScaleMode(sprite, SDL_SCALEMODE_NEAREST);
}

Mark::~Mark(){
	SDL_DestroyTexture(sprite);
}