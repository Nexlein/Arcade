/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** ADisplayModule
*/

/// @file ADisplayModule.hpp
/// @brief Abstract base class for display modules in the Arcade project

#pragma once

#include <queue>
#include <string>

#include "IDisplayModule.hpp"

namespace arcade {

    /// @brief Abstract base class for display modules
    ///
    /// Provides common functionality and state management for all display modules.
    class ADisplayModule : public IDisplayModule {
        public:
        /// @brief Constructor for the ADisplayModule class
        /// @param name The name of the display module (default is "Unnamed Display")
        /// @param context The context of the current display module (default if 800x600 in PIXEL mode)
        ADisplayModule(std::string name = "Unnamed Display", RenderContext context = {800, 600, CoordinateSpace::PIXEL});
        virtual ~ADisplayModule() = default;

        // --- Getters ---

        /// @brief Gets the type of the display module
        /// @return The module type
        ModuleType getType() const override;

        /// @brief Gets the name of the display module
        /// @return The module name
        const std::string& getName() const override;

        /// @brief Gets the last key event
        /// @return The last key event
        Key getKey() override;

        /// @brief Gets the last mouse event
        /// @return The last mouse event
        MouseEvent getMouseEvent() override;

        /// @brief Gets the delta time
        /// @return The delta time
        float getDeltaTime() const override;

        /// @brief Gets the width of the display module
        /// @return The width
        int getWidth() const override;

        /// @brief Gets the height of the display module
        /// @return The height
        int getHeight() const override;

        // --- Setters ---

        /// @brief Sets the title of the display module
        /// @param title The new title
        void setTitle(const std::string& title) override;

        /// @brief Sets the size of the display module window
        /// @param width The new width
        /// @param height The new height
        void setWindowSize(int width, int height) override;

        /// @brief Sets the fullscreen mode of the display module
        /// @param fullscreen The new fullscreen mode
        void setFullscreen(bool fullscreen) override;

        /// @brief Sets the render context of the display module
        /// @param context The new render context
        void setRenderContext(const RenderContext& context) override;

        protected:
        /// @brief The name of the display module
        std::string _name;

        /// @brief The title of the display window
        std::string _title;

        /// @brief The render context containing dimensions and coordinate space
        RenderContext _context;

        /// @brief Whether the display is in fullscreen mode
        bool _fullScreen;

        /// @brief Timing variables for delta time calculation
        float _currentTime;

        /// @brief The last recorded time for delta time calculation
        float _lastTime;

        /// @brief Queue to store key events
        std::queue<Key> _keyEvent;

        /// @brief Queue to store mouse events
        std::queue<MouseEvent> _mouseEvent;
    };
}  // namespace arcade
