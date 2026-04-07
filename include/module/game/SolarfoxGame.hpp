/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SolarfoxGame
*/

#pragma once

#include "AGameModule.hpp"
#include "IDisplayModule.hpp"
#include <array>
#include <vector>
#include <random>

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

        struct Enemy {
            Position pos;
            Direction dir;
            Direction shotDir;
            float timeSinceLastShot;
            std::string spritePath;
            Anchor anchor;
        };

        void updatePosition();
        void handleSpaceshipDirection(Key key);
        void initPowerups();
        void initEnemies();
        void detectCollisions();
        void nextLevel();

        Entity _ship;
        std::string _currentSpritePath;
        char _shipChar;
        Position _shipPosition;
        Direction _shipDirection;
        float _shipSpeed;

        int _level;
        std::vector<Bullet> _bullets;
        float _bulletSpeed;
        std::vector<Powerup> _powerups;
        std::array<Enemy, 4> _enemies;
        std::vector<Bullet> _enemyBullets;
        float _enemyFireRate;
        std::mt19937 _rng;

        float _timeSinceLastMove;
        float _moveInterval;
    };
}  // namespace arcade
