/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** LIBCACADisplay
*/

#pragma once

#include "ADisplayModule.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

namespace arcade {
    /// @brief ALLEGRO5 implementation of the IDisplayModule interface
    class ALLEGRO5 : public ADisplayModule {
        public:
        ALLEGRO5();
        ~ALLEGRO5();

        /// @brief Initialize the ALLEGRO5 display module
        /// @throw std::runtime_error if initialization fails
        void init() override;

        /// @brief Stop and cleanup the ALLEGRO5 display module
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


        /// @brief Check if the specified file has a valid format
        /// @param path The path to the file
        /// @return True if the format is valid, false otherwise
        bool isValidFormat(const std::string& path);

        // void applyAnchor(Anchor anchor, SDL_Rect& dst);
        // void applyScaling(SDL_Rect& dst);
        Viewport computeViewport() const override;

        /// @brief The SDL2 window
        ALLEGRO_DISPLAY* _win;

        /// @brief The SDL2 renderer
    };
}  // namespace arcade
