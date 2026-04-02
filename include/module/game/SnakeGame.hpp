/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** SnakeGame
*/

#pragma once

#include <deque>

#include "AGameModule.hpp"

namespace arcade {
    /// @brief Snake game implementation
    class SnakeGame : public AGameModule {
        public:
        SnakeGame();

        /// @brief Update the game state
        /// @param elapsedTime Time elapsed since last update
        void update(float elapsedTime) override;

        /// @brief Handle input events
        /// @param key The key that was pressed
        void handleInput(Key key) override;

        /// @brief Handle mouse input
        /// @param mouseEvent The mouse event
        void handleInput(MouseEvent mouseEvent) override;

        /// @brief get all entities to be rendered
        /// @return Const reference to vector of entities to render
        const std::vector<Entity>& getEntities() const override;

        /// @brief get all UI text elements to be rendered
        /// @return Const reference to vector of text elements to render
        const std::vector<Text>& getUIText() const override;

        /// @brief Restart the game
        void restart() override;

        private:
        float _timeSinceLastMove;
        float _moveInterval;

        Orientation _currentDir;
        Orientation _nextDir;

        std::deque<Position> _snakeBody;
        std::vector<Position> _fruits;

        /// @brief Move the snake in the current direction, handle collisions and fruit consumption
        void moveSnake();

        /// @brief Spawn a fruit at a random position not occupied
        void spawnFruit();

        /// @brief Update the snake body and head entities
        void updateSnakeEntities();

        /// @brief Update the fruit entities
        void updateFruitEntities();

        /// @brief Update the wall entities
        void updateWallEntities();

        /// @brief Update the floor entities
        void updateFloorEntities();

        /// @brief Set the oriented sprites for snake
        void setSnakeOrientedSprites();
    };
}  // namespace arcade
