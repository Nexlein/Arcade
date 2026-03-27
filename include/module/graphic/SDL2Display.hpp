/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** SDL2Display
*/

/// @file SDL2Display.hpp
/// @brief SDL2 implementation of the IDisplayModule interface

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_rect.h>
#include <map>

#include "ADisplayModule.hpp"

namespace arcade {
    class SDL2Display : public ADisplayModule {
        public:
        SDL2Display();
        ~SDL2Display();

        /// @brief Initialize the SDL2 display module
        /// @throw std::runtime_error if initialization fails
        void init() override;

        /// @brief Stop and cleanup the SDL2 display module
        void stop() override;

        /// @brief Clear the screen
        void clear() override;

        /// @brief Display the current frame
        void display() override;

        /// @brief Draw an entity on the screen
        /// @param entity The entity to draw
        void drawEntity(const Entity& entity) override;

        /// @brief Draw text on the screen
        /// @param text The text to draw
        void drawText(const Text& text) override;

        /// @brief Draw a rectangle on the screen
        /// @param rect The rectangle to draw
        /// @param color The color of the rectangle
        void drawRectangle(const Rect& rect, const Color& color) override;

        /// @brief Poll for input events
        void pollEvents() override;

        /// @brief Checks if the display is open
        /// @return True if the display is open, false otherwise
        bool isOpen() const override;

        private:
        /// @brief Get a font from the cache or load a new one
        /// @param path The path to the font file
        /// @param size The size of the font
        /// @return A pointer to the loaded font
        /// @throw std::runtime_error if the font cannot be loaded
        TTF_Font* getFont(const std::string& path, int size);

        /// @brief Try to open a font from the specified path
        /// @param fontPath The path to the font file
        /// @param size The size of the font
        /// @return A pointer to the loaded font, or nullptr if failed
        TTF_Font* tryOpenFont(const std::string& fontPath, int size);

        /// @brief Get a fallback font if the specified font cannot be loaded
        /// @param size The size of the font
        /// @return A pointer to the fallback font
        TTF_Font* getFallbackFont(int size);

        /// @brief Get a sprite from the cache or load a new one
        /// @param path The path to the sprite file
        /// @return A pointer to the loaded sprite
        SDL_Texture* getSprite(const std::string& path);

        /// @brief Check if the specified file has a valid format
        /// @param path The path to the file
        /// @return True if the format is valid, false otherwise
        bool isValidFormat(const std::string& path);

        /// @brief Cleanup all loaded fonts
        void stopFont();

        /// @brief Cleanup all loaded sprites
        void stopSprite();

        void applyAnchor(Anchor anchor, SDL_Rect& dst);
        void applyScaling(SDL_Rect& dst);

        /// @brief The SDL2 window
        SDL_Window* _win;

        /// @brief The SDL2 renderer
        SDL_Renderer* _renderer;

        /// @brief Cache for loaded fonts, keyed by (path, size)
        std::map<std::pair<std::string, int>, TTF_Font*> _fontCache;

        /// @brief Cache for loaded sprites, keyed by file path
        std::map<std::string, SDL_Texture*> _spriteCache;
    };
}  // namespace arcade
