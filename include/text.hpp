#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

/// @brief A class for rendering text using SDL3_ttf.
class Text {
private:
    /// @brief The font used for rendering text.
    TTF_Font* font = NULL;
    
    /// @brief The color of the text.
    SDL_Color color;
    
    /// @brief The SDL renderer used for rendering text.
    SDL_Renderer* renderer = NULL;

    /// @brief The text rendering engine.
    /// This is used to create text surfaces.
    TTF_TextEngine *engine = NULL;
    
    /// @brief The surface that holds the rendered text.
    /// This surface is used to create a texture for rendering.
    SDL_Surface *textBox = NULL;
    
    /// @brief Text object for rendering.
    TTF_Text *text = NULL;

    /// @brief Padding for the text box.
    int padding = 15;
    
    /// @brief Border width for the text box.
    int borderWidth = 5;

    /// @brief The texture used for rendering the text.
    SDL_Texture *texture = NULL;
    
    void create_text_box(int w, int h);
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

    /// @brief Sets the color of the text.
    /// @param r The red component (0-255).
    /// @param g The green component (0-255).
    /// @param b The blue component (0-255).
    /// @param a The alpha component (0-255).
    void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    /// @brief Sets the text to be rendered.
    /// @param msg The text to render.
    void set_text(const char *msg);
    
    /// @brief Sets the padding for the text box.
    /// @param p The padding to set.
    void set_padding(int p);

    /// @brief Sets the border width for the text box.
    /// @param bw The border width to set.
    void set_border_width(int bw);

    /// @brief Refreshes the texture used for rendering text.
    /// This method adjusts the text box size based on the current text dimensions.
    void refresh_texture();
    
    /// @brief Renders the text to the screen.
    /// @param renderer The SDL renderer to use for rendering text.
    void render_text();

};

#endif // TEXT_HPP