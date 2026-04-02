/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SolarfoxGame
*/

#pragma once

#include "AGameModule.hpp"
#include "IDisplayModule.hpp"

namespace arcade {
    /// @brief Solarfox game implementation
    class Solarfox : public AGameModule {
        public:
        Solarfox();

        /// @brief Update the game state
        /// @param elapsedTime Time elapsed since last update
        void update(float elapsedTime) override;

        /// @brief Handle input events
        /// @param key The key that was pressed
        void handleInput(Key key) override;

        /// @brief Handle mouse input
        /// @param mouseEvent The mouse event
        void handleInput(MouseEvent mouseEvent) override;

        /// @brief Restart the game
        void restart() override;

        private:
        void moveSpaceship();
        void rotateSpaceship(Key key);
        enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

        float _timeSinceLastMove;
        float _moveInterval;

        Entity _spaceship;
        std::string _currentSpritePath;
        Position _spaceshipPos;
        Direction _nextDir;

    };
}  // namespace arcade
