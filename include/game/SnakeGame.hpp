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

        /// @brief Get the current score
        /// @return Player's current score
        int getScore() const override;

        /// @brief Restart the game
        void restart() override;

        /// @brief Get the render context for this game (e.g., window size, coordinate space)
        /// @return RenderContext containing rendering parameters for this game
        RenderContext getRenderContext() const override;

        private:
        enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

        float _timeSinceLastMove;
        float _moveInterval;

        Direction _currentDir;
        Direction _nextDir;

        std::deque<Position> _snakeBody;
        std::vector<Position> _fruits;

        mutable std::vector<Entity> _entities;
        mutable std::vector<Text> _uiTexts;

        /// @brief Move the snake in the current direction, handle collisions and fruit consumption
        void moveSnake();

        /// @brief Spawn a fruit at a random position not occupied
        void spawnFruit();
    };
}  // namespace arcade
