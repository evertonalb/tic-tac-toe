#include "text.hpp"
#include <stdexcept>

void Text::create_text_box(int w, int h, int borderWidth){
	if (textBox){
		SDL_DestroySurface(textBox);
		textBox = nullptr;
	}
	
	textBox = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);
	if (!textBox) {
		throw std::runtime_error("Failed to create text box surface: " + std::string(SDL_GetError()));
	}

	SDL_Window *win = SDL_GetRenderWindow(renderer);
	int winWidth, winHeight;
	SDL_GetWindowSize(win, &winWidth, &winHeight);
	
	SDL_Rect target = {borderWidth, borderWidth, w - 2 * borderWidth, h - 2 * borderWidth};

	SDL_ClearSurface(textBox, 255, 255, 255, 255); // Clear with white color
	SDL_ClearError();
	SDL_FillSurfaceRect(textBox, &target, SDL_MapSurfaceRGBA(textBox, 0, 0, 0, 255)); // Fill with black color
}

Text::Text(const std::string &fontPath, int fontSize, SDL_Renderer *renderer, SDL_Color color) : Text(fontPath, fontSize, renderer)
{
	set_color(color.r, color.g, color.b, color.a);
}

Text::Text(const std::string &fontPath, int fontSize, SDL_Renderer *renderer) : renderer(renderer), color{255, 255, 255, 255}
{
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		throw std::runtime_error("Failed to load font: " + std::string(SDL_GetError()));
	}
	
	engine = TTF_CreateSurfaceTextEngine();
}

Text::~Text(){
	TTF_CloseFont(font);
	TTF_DestroySurfaceTextEngine(engine);
	SDL_DestroySurface(textBox);
}

void Text::render(const std::string &message, int borderWidth, int padding){
	// Create text object
	TTF_Text *text = TTF_CreateText(engine, font, message.c_str(), message.size());
	if (!text) {
		throw std::runtime_error("Failed to create text: " + std::string(SDL_GetError()));
	}
	TTF_SetTextColor(text, color.r, color.g, color.b, color.a);
	TTF_SetFontWrapAlignment(font, TTF_HORIZONTAL_ALIGN_CENTER); // Center text horizontally
	
	int textWidth, textHeight;
	TTF_GetTextSize(text, &textWidth, &textHeight);

	SDL_DestroySurface(textBox);
	create_text_box( // The text box will be just large enough to fit the text
		textWidth + 2 * (padding + borderWidth),
		textHeight + 2 * (padding + borderWidth),
		borderWidth
	);
	
	if (!textBox) {
		TTF_DestroyText(text);
		throw std::runtime_error("Failed to create text box surface: " + std::string(SDL_GetError()));
	}

	TTF_DrawSurfaceText(text, borderWidth + padding, textBox->h / 2 - textHeight / 2, textBox); // Center text vertically
																								
	// Render texture centered in the window
	SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, textBox);
	
	int width, height;
	SDL_GetWindowSize(SDL_GetRenderWindow(renderer), &width, &height);
	SDL_FRect target = {
		(float) width / 2 - textBox->w / 2, 
		(float) height / 2 - textBox->h / 2, 
		(float) textBox->w, 
		(float) textBox->h
	};
	
	SDL_RenderTexture(renderer, txt, NULL, &target);
	
	SDL_DestroyTexture(txt);
}

void Text::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}
