#include "text.hpp"
#include <stdexcept>

Text::Text(const std::string &fontPath, int fontSize, SDL_Renderer *renderer, SDL_Color color) :
	Text(fontPath, fontSize, renderer)
{
	set_color(color.r, color.g, color.b, color.a);
}

Text::Text(const std::string &fontPath, int fontSize, SDL_Renderer *renderer) : renderer(renderer), color{255, 255, 255, 255}
{
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		throw std::runtime_error("Failed to load font: " + std::string(SDL_GetError()));
	}
}

Text::~Text(){
	TTF_CloseFont(font);
}

void Text::render(const std::string &message, int x, int y){
	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), message.size(), color);
	if (!surface) {
		throw std::runtime_error("Failed to create text surface: " + std::string(SDL_GetError()));
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_DestroySurface(surface);
		throw std::runtime_error("Failed to create texture from surface: " + std::string(SDL_GetError()));
	}

	SDL_FRect target = {(float)x, (float)y, (float)surface->w, (float)surface->h};
	SDL_RenderTexture(renderer, texture, NULL, &target);

	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);
}

void Text::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}
