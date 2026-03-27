/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** AGameModule
*/

/// @file AGameModule.hpp
/// @brief Abstract base class for game modules

#pragma once

#include "IGameModule.hpp"

namespace arcade {

    /// @class AGameModule
    /// @brief Abstract implementation of IGameModule that provides getType()
    ///
    /// This class implements the getType() method returning ModuleType::GAME.
    /// All concrete game modules (Snake, Pacman, etc.) should inherit from
    /// this class instead of IGameModule directly.
    class AGameModule : public IGameModule {
        public:
        /// @brief Virtual destructor
        AGameModule(std::string name = "Unnamed Game", GameState initialState = GameState::MENU, RenderContext context = RenderContext(800, 600, CoordinateSpace::PIXEL));
        virtual ~AGameModule() = default;

        /// @brief Get the render context of the current game (window size, space coordinate)
        /// @return RenderContext containing rendering parameters for this game
        RenderContext getRenderContext() const override;

        /// @brief Get the type of this module
        /// @return ModuleType::GAME
        ModuleType getType() const override;

        /// @brief Get the name of this game
        /// @return Name of the game (e.g., "Snake", "Pacman", "Nibbler")
        const std::string& getName() const override;

        /// @brief Get the current game state
        /// @return Current state (menu, running, paused, game over, won)
        GameState getState() const override;

        /// @brief Get the current score
        /// @return Player's current score
        int getScore() const override;

        /// @brief Stop the game and clean up resources
        void stop() override;

        /// @brief Pause the game
        void pause() override;

        /// @brief Resume the game
        void resume() override;

        /// @brief Initialize the game state
        void init() override;

        protected:
        /// @brief Append common UI texts (controls) to the given vector
        void appendCommonUITexts(std::vector<Text>& uiTexts) const;

        std::string _name;
        GameState _state;

        RenderContext _context;

        int _score;
    };
}  // namespace arcade
