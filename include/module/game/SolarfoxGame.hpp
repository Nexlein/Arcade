/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SolarfoxGame
*/

#pragma once

#include "AGameModule.hpp"
#include "IDisplayModule.hpp"
#include <vector>

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

        enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

        struct Bullet {
            Position pos;
            Direction dir;
            float distanceTraveled;
        };

        struct Powerup {
            Position pos;
            bool collected;
        };

        void updatePosition();
        void handleSpaceshipDirection(Key key);
        void initPowerups();
        void detectCollisions();

        Entity _ship;
        std::string _currentSpritePath;
        Position _shipPosition;
        Direction _shipDirection;

        std::vector<Bullet> _bullets;
        std::vector<Powerup> _powerups;
        int _level;

        float _timeSinceLastMove;
        float _moveInterval;
    };
}  // namespace arcade
