#include "mark.hpp"

#include <SDL3_image/SDL_image.h>
#include <stdexcept>

Mark::Mark(const Mark &other) :
	start(other.start), 
	stride(other.stride),
	srcrect(other.srcrect)
{
	sprite = SDL_DuplicateSurface(other.sprite);
	if (!sprite){
		throw std::runtime_error("Failed to duplicate surface: " + std::string(SDL_GetError()));
	}
}

Mark::Mark(const char *file, SDL_Renderer *renderer, SDL_FRect start, int stride) : start(start), stride(stride) {
	sprite = IMG_Load(file);
	if (!sprite){
		throw std::runtime_error("Failed to create surface: " + std::string(SDL_GetError()));
	}

	randomize_sprite();
}

Mark &Mark::operator=(const Mark &other){
	if (this != &other) {
		start = other.start;
		stride = other.stride;
		srcrect = other.srcrect;

		sprite = SDL_DuplicateSurface(other.sprite);
		if (!sprite) {
			throw std::runtime_error("Failed to duplicate surface: " + std::string(SDL_GetError()));
		}
	}
	return *this;
}

void Mark::randomize_sprite(){
	int current = srcrect.x  / 35;
	int n = current;
	
	while (n == current) n = SDL_rand(4);
	
	int step = stride * n;

	srcrect = start;
	srcrect.x += step;
}

void Mark::render_mark(SDL_Renderer *renderer, SDL_FRect &target){
	if (!texture){
		texture = SDL_CreateTextureFromSurface(renderer, sprite);		
		SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	}

	SDL_RenderTexture(renderer, texture, &srcrect, &target);
}

Mark::~Mark(){
	SDL_DestroySurface(sprite);
	SDL_DestroyTexture(texture);
}