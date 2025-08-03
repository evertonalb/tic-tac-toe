#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

/// @brief A class for rendering text using SDL3_ttf.
class Text {
private:
    /// @brief The font used for rendering text.
    TTF_Font* font;
    
    /// @brief The color of the text.
    SDL_Color color;
    
    /// @brief The SDL renderer used for rendering text.
    SDL_Renderer* renderer;
    
    /// @brief The text rendering engine.
    /// This is used to create text surfaces.
    TTF_TextEngine *engine;
    
    /// @brief The surface that holds the rendered text.
    /// This surface is used to create a texture for rendering.
    SDL_Surface *textBox;
    
    void create_text_box(int w, int h, int borderWidth);
public:
    /// @brief Construct a Text object with a specified font, size, renderer, and color.
    /// @param fontPath Path to the font file.
    /// @param fontSize The size of the font.
    /// @param renderer The SDL renderer to use for rendering text.
    /// @param color The color of the text.
    Text(const std::string& fontPath, int fontSize, SDL_Renderer* renderer, SDL_Color color);
    
    /// @brief Construct a Text object with a specified font, size, and renderer.
    /// @param fontPath Path to the font file.
    /// @param fontSize The size of the font.
    /// @param renderer The SDL renderer to use for rendering text.
    Text(const std::string& fontPath, int fontSize, SDL_Renderer* renderer);
    ~Text();

    /// @brief Renders text in a box centered in the window.
    /// @param message The text to render.
    /// @param borderWidth The width of the border around the text box.
    /// @param padding The padding inside the text box.
    void render(const std::string& message, int borderWidth, int padding);

    /// @brief Sets the color of the text.
    /// @param r The red component (0-255).
    /// @param g The green component (0-255).
    /// @param b The blue component (0-255).
    /// @param a The alpha component (0-255).
    void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

};

#endif // TEXT_HPP