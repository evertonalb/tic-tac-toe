#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Text {
private:
    TTF_Font* font;
    SDL_Color color;
    SDL_Renderer* renderer;
public:
    Text(const std::string& fontPath, int fontSize, SDL_Renderer* renderer, SDL_Color color);
    Text(const std::string& fontPath, int fontSize, SDL_Renderer* renderer);
    ~Text();

    void render(const std::string& message, int x, int y);
    void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

};

#endif // TEXT_HPP