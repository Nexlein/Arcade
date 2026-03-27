/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** SnakeGame
*/

#include "SnakeGame.hpp"

#include <random>

const std::string GAMENAME = "Snake";

arcade::SnakeGame::SnakeGame() : AGameModule(GAMENAME, GameState::RUNNING, RenderContext(40, 30, CoordinateSpace::GRID)) { init(); }

void arcade::SnakeGame::update(float elapsedTime)
{
    if (_state != GameState::RUNNING) return;

    _timeSinceLastMove += elapsedTime;
    if (_timeSinceLastMove >= _moveInterval) {
        moveSnake();
        _timeSinceLastMove = 0.0;
    }
}

void arcade::SnakeGame::handleInput(Key key)
{
    if (key == Key::P) {
        if (_state == GameState::RUNNING)
            pause();
        else if (_state == GameState::PAUSED)
            resume();
        return;
    }

    if (key == Key::UP || key == Key::Z)
        if (_currentDir != Direction::DOWN) _nextDir = Direction::UP;
    if (key == Key::DOWN || key == Key::S)
        if (_currentDir != Direction::UP) _nextDir = Direction::DOWN;
    if (key == Key::LEFT || key == Key::Q)
        if (_currentDir != Direction::RIGHT) _nextDir = Direction::LEFT;
    if (key == Key::RIGHT || key == Key::D)
        if (_currentDir != Direction::LEFT) _nextDir = Direction::RIGHT;
}

void arcade::SnakeGame::handleInput(MouseEvent mouseEvent)
{
    (void)mouseEvent;
}

const std::vector<arcade::Entity>& arcade::SnakeGame::getEntities() const
{
    _entities.clear();

    for (size_t i = 0; i < _snakeBody.size(); ++i) {
        Entity part;
        part.pos = _snakeBody[i];
        part.size = {1, 1};

        if (i == 0) {
            part.character = 'O';
            part.color = Colors::YELLOW;
            part.spritePath = "sprite/snakeHead.png";
        } else {
            part.character = 'o';
            part.color = Colors::GREEN;
            part.spritePath = "sprite/snakeBody.png";
        }
        _entities.push_back(part);
    }

    for (const auto& fruitPos : _fruits) {
        Entity fruit;
        fruit.pos = fruitPos;
        fruit.size = {1, 1};
        fruit.character = '#';
        fruit.color = Colors::RED;
        fruit.spritePath = "sprite/fruit.png";
        _entities.push_back(fruit);
    }

    for (int x = 0; x < _context.width; x++) {
        Entity wallTop;
        wallTop.pos = {static_cast<float>(x), 0};
        wallTop.size = {1, 1};
        wallTop.character = '#';
        wallTop.color = Colors::MAGENTA;
        wallTop.spritePath = "sprite/wall.png";
        _entities.push_back(wallTop);

        Entity wallBottom;
        wallBottom.pos = {static_cast<float>(x), static_cast<float>(_context.height - 1)};
        wallBottom.size = {1, 1};
        wallBottom.character = '#';
        wallBottom.color = Colors::MAGENTA;
        wallBottom.spritePath = "sprite/wall.png";
        _entities.push_back(wallBottom);
    }

    for (int y = 0; y < _context.height; y++) {
        Entity wallLeft;
        wallLeft.pos = {0, static_cast<float>(y)};
        wallLeft.size = {1, 1};
        wallLeft.character = '#';
        wallLeft.color = Colors::MAGENTA;
        wallLeft.spritePath = "sprite/wall.png";
        _entities.push_back(wallLeft);

        Entity wallRight;
        wallRight.pos = {static_cast<float>(_context.width - 1), static_cast<float>(y)};
        wallRight.size = {1, 1};
        wallRight.character = '#';
        wallRight.color = Colors::MAGENTA;
        wallRight.spritePath = "sprite/wall.png";
        _entities.push_back(wallRight);
    }

    return _entities;
}

const std::vector<arcade::Text>& arcade::SnakeGame::getUIText() const
{
    _uiTexts.clear();

    std::string scoreStr = "Score: " + std::to_string(_score);
    _uiTexts.push_back(Text(scoreStr, 1, 0, Anchor::TOP_LEFT, Colors::WHITE, 20));

    if (_state == GameState::GAME_OVER)
        _uiTexts.push_back(Text("GAME OVER", static_cast<float>(_context.width) / 2, static_cast<float>(_context.height) / 2, Anchor::CENTER, Colors::RED, 30));

    appendCommonUITexts(_uiTexts);

    return _uiTexts;
}

void arcade::SnakeGame::restart()
{
    _state = GameState::RUNNING;
    _score = 0;
    _timeSinceLastMove = static_cast<float>(0.0);
    _moveInterval = static_cast<float>(0.15);
    _currentDir = Direction::NONE;
    _nextDir = Direction::NONE;

    _snakeBody.clear();
    int midX = _context.width / 2;
    int midY = _context.height / 2;
    _snakeBody.push_back({static_cast<float>(midX), static_cast<float>(midY)});
    _snakeBody.push_back({static_cast<float>(midX - 1), static_cast<float>(midY)});
    _snakeBody.push_back({static_cast<float>(midX - 2), static_cast<float>(midY)});
    _snakeBody.push_back({static_cast<float>(midX - 3), static_cast<float>(midY)});

    _fruits.clear();
    spawnFruit();
}

void arcade::SnakeGame::moveSnake()
{
    if (_nextDir != Direction::NONE) {
        if (_nextDir == Direction::UP && _currentDir != Direction::DOWN)
            _currentDir = _nextDir;
        else if (_nextDir == Direction::DOWN && _currentDir != Direction::UP)
            _currentDir = _nextDir;
        else if (_nextDir == Direction::LEFT && _currentDir != Direction::RIGHT)
            _currentDir = _nextDir;
        else if (_nextDir == Direction::RIGHT && _currentDir != Direction::LEFT)
            _currentDir = _nextDir;
    }

    Position nextHead = _snakeBody.front();

    switch (_currentDir) {
        case Direction::UP:
            nextHead.y -= 1;
            break;
        case Direction::DOWN:
            nextHead.y += 1;
            break;
        case Direction::LEFT:
            nextHead.x -= 1;
            break;
        case Direction::RIGHT:
            nextHead.x += 1;
            break;
        case Direction::NONE:
            return;
    }

    /// Wall Collision (Game Over)
    if (nextHead.x < 1 || nextHead.x >= _context.width - 1 || nextHead.y < 1 || nextHead.y >= _context.height - 1) {
        _state = GameState::GAME_OVER;
        return;
    }

    /// Self Collision (Game Over)
    for (size_t i = 0; i < _snakeBody.size() - 1; ++i) {
        if (_snakeBody[i].x == nextHead.x && _snakeBody[i].y == nextHead.y) {
            _state = GameState::GAME_OVER;
            return;
        }
    }

    /// Add the new head
    _snakeBody.push_front(nextHead);

    /// Check if we ate a fruit
    bool ateFruit = false;
    for (auto& fruitPos : _fruits) {
        if (fruitPos.x == nextHead.x && fruitPos.y == nextHead.y) {
            _score += 10;
            _fruits.clear();
            spawnFruit();
            ateFruit = true;
            break;
        }
    }
    /// If we didn't eat a fruit, remove the tail
    if (!ateFruit) _snakeBody.pop_back();
}

void arcade::SnakeGame::spawnFruit()
{
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> distX(1, _context.width - 2);
    std::uniform_int_distribution<int> distY(1, _context.height - 2);

    bool validPosition = false;
    float randX = 0;
    float randY = 0;

    while (!validPosition) {
        randX = static_cast<float>(distX(rng));
        randY = static_cast<float>(distY(rng));
        validPosition = true;

        for (const auto& part : _snakeBody) {
            if (part.x == randX && part.y == randY) {
                validPosition = false;
                break;
            }
        }

        for (const auto& fruit : _fruits) {
            if (fruit.x == randX && fruit.y == randY) {
                validPosition = false;
                break;
            }
        }
    }
    _fruits.push_back({randX, randY});
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::SnakeGame();
    }
}
