/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SolarfoxGame
*/

#include "SolarfoxGame.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

const std::string GAMENAME = "Solarfox";
const float MOVE_INTERVAL = 0.02f;
const float SPACESHIP_SPEED = 6.0f;

arcade::Solarfox::Solarfox() : AGameModule(GAMENAME, GameState::RUNNING, RenderContext(800, 600, CoordinateSpace::PIXEL)) { init(); }

// spaceship hitbox: triangle 
void arcade::Solarfox::update(float elapsedTime)
{
    if (_state == GameState::RUNNING) {
        _timeSinceLastMove += elapsedTime;
        if (_timeSinceLastMove >= _moveInterval) {
            moveSpaceship();
            _timeSinceLastMove = 0.0;
        }
    }

    _entities.clear();
    _uiText.clear();

    Entity limit2;
    limit2.pos = {0, 0};
    limit2.size = {800,600};
    limit2.color = Colors::MAGENTA;
    _entities.push_back(limit2);

    Entity limit;
    limit.pos = {80, 80};
    limit.size = {640, 440};
    limit.color = Colors::GREEN;
    _entities.push_back(limit);

    _spaceship.pos = _spaceshipPos;
    _spaceship.anchor = Anchor::CENTER;
    _spaceship.size = {65, 65};
    _spaceship.character = '>';
    _spaceship.color = Colors::CYAN;
    _spaceship.backgroundColor = Colors::BLACK;
    _spaceship.spritePath = _currentSpritePath;
    _entities.push_back(_spaceship);

    // Update UI texts
    appendCommonUITexts();
}

void arcade::Solarfox::moveSpaceship()
{
    switch (_nextDir) {
        case Direction::UP:
            _spaceshipPos.y -= SPACESHIP_SPEED;
            break;
        case Direction::DOWN:
            _spaceshipPos.y += SPACESHIP_SPEED;
            break;
        case Direction::LEFT:
            _spaceshipPos.x -= SPACESHIP_SPEED;
            break;
        case Direction::RIGHT:
            _spaceshipPos.x += SPACESHIP_SPEED;
            break;
        case Direction::NONE:
            return;
    }

    // Keep spaceship within bounds (80,80) to (720,520)
    if (_spaceshipPos.x < 100 || _spaceshipPos.x > 700 || _spaceshipPos.y < 100 || _spaceshipPos.y > 500) {
        _state = GameState::GAME_OVER;
        return;
    }
}

void arcade::Solarfox::rotateSpaceship(Key key)
{
    if (key == Key::UP || key == Key::Z)
        _currentSpritePath = "sprite/spaceship1.png";
    if (key == Key::DOWN || key == Key::S)
        _currentSpritePath = "sprite/spaceship3.png";
    if (key == Key::LEFT || key == Key::Q)
        _currentSpritePath = "sprite/spaceship4.png";
    if (key == Key::RIGHT || key == Key::D)
        _currentSpritePath = "sprite/spaceship2.png";
}

void arcade::Solarfox::handleInput(Key key)
{
    if (key == Key::P) {
        if (_state == GameState::RUNNING)
            pause();
        else if (_state == GameState::PAUSED)
            resume();
        return;
    }

    if (key == Key::UP || key == Key::Z)
        _nextDir = Direction::UP;
    if (key == Key::DOWN || key == Key::S)
        _nextDir = Direction::DOWN;
    if (key == Key::LEFT || key == Key::Q)
        _nextDir = Direction::LEFT;
    if (key == Key::RIGHT || key == Key::D)
        _nextDir = Direction::RIGHT;

    rotateSpaceship(key);
}

void arcade::Solarfox::handleInput(MouseEvent mouseEvent)
{
    (void)mouseEvent;
}

void arcade::Solarfox::restart()
{
    int midX = _context.width / 2;
    int midY = _context.height / 2;

    _state = GameState::RUNNING;
    _score = 0;
    _timeSinceLastMove = static_cast<float>(0.0);
    _moveInterval = static_cast<float>(MOVE_INTERVAL);
    _nextDir = Direction::NONE;
    _spaceshipPos = {static_cast<float>(midX), static_cast<float>(midY)};
    _currentSpritePath = "sprite/spaceship1.png";
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::Solarfox();
    }
}
