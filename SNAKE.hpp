/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** snake
*/

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>

#include "AGameModule.hpp"

namespace arcade {
    class SnakeGame : public AGameModule {
        public:
        SnakeGame();

        void init() override;
        void stop() override;

        void update(float deltaTime) override;
        void handleInput(Key key) override;

        const std::vector<Entity>& getEntities() const override;
        const std::vector<Text>& getUIText() const override;

        /// Getters

        int getScore() const override;
        GameState getState() const override;
        const std::string& getName() const override;

        void restart() override;
        void pause() override;
        void resume() override;
        RenderContext getRenderContext() const override;

        private:
        enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

        GameState _state;
        int _score;
        float _timeSinceLastMove;
        float _moveInterval;

        int _width;
        int _height;
        Direction _currentDir;
        std::deque<Position> _snakeBody;
        std::vector<Position> _fruits;

        mutable std::vector<Entity> _entities;
        mutable std::vector<Text> _uiTexts;

        void moveSnake();
        void spawnFruit();
    };
}  // namespace arcade

#endif /* !SNAKE_HPP */
