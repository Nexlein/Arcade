/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SolarfoxGame
*/

#include "SolarfoxGame.hpp"
#include <algorithm>

const std::string GAMENAME = "Solarfox";
const float MOVE_INTERVAL = 0.0167f;
const float SPACESHIP_SPEED = 6.0f;
const float BULLET_SPEED = 16.0f;

const int CELL_SIZE = 60;
const int START_X = 200;
const int START_Y = 100;
const int END_X = 600;
const int END_Y = 500;

arcade::Solarfox::Solarfox() : AGameModule(GAMENAME, GameState::RUNNING, RenderContext(800, 600, CoordinateSpace::PIXEL)) { init(); }

    // Entity limit2;
    // limit2.pos = {0, 0};
    // limit2.size = {800,600};
    // limit2.color = Colors::RED;
    // _entities.push_back(limit2);

    // Entity limit;
    // limit.pos = {100, 100};
    // limit.size = {600, 400};
    // limit.color = Colors::BLACK;
    // _entities.push_back(limit);
// spaceship hitbox: triangle / rec
// mettre un range au tir.
// ajouter des bonhommes. (diff speed)
void arcade::Solarfox::update(float elapsedTime)
{
    if (_state == GameState::RUNNING) {
        _timeSinceLastMove += elapsedTime;
        if (_timeSinceLastMove >= _moveInterval) {
            updatePosition();
            detectCollisions();
            _timeSinceLastMove = 0.0;
        }
    }

    _entities.clear();
    _uiText.clear();

    for (const auto& bullet : _bullets) {
        Entity bulletEntity;
        bulletEntity.pos = bullet.pos;
        bulletEntity.size = {3, 3};
        bulletEntity.character = '*';
        bulletEntity.color = Colors::YELLOW;
        bulletEntity.spritePath = "sprite/bullet.png";
        _entities.push_back(bulletEntity);
    }

    for (const auto& powerup : _powerups) {
        if (powerup.collected) continue;

        Entity powerupEntity;
        powerupEntity.pos = powerup.pos;
        powerupEntity.size = {30, 30};
        powerupEntity.character = 'P';
        powerupEntity.color = Colors::GREEN;
        powerupEntity.spritePath = "sprite/diamond.png";
        _entities.push_back(powerupEntity);
    }

    _ship.pos = _shipPosition;
    _ship.anchor = Anchor::CENTER;
    _ship.size = {65, 65};
    _ship.character = '>';
    _ship.color = Colors::CYAN;
    _ship.backgroundColor = Colors::BLACK;
    _ship.spritePath = _currentSpritePath;
    _entities.push_back(_ship);

    // Update UI texts
    appendCommonUITexts();
}

void arcade::Solarfox::updatePosition()
{
    switch (_shipDirection) {
        case Direction::UP:
            _shipPosition.y -= SPACESHIP_SPEED;
            break;
        case Direction::DOWN:
            _shipPosition.y += SPACESHIP_SPEED;
            break;
        case Direction::LEFT:
            _shipPosition.x -= SPACESHIP_SPEED;
            break;
        case Direction::RIGHT:
            _shipPosition.x += SPACESHIP_SPEED;
            break;
        case Direction::NONE:
            return;
    }

    for (auto& bullet : _bullets) {
        switch (bullet.dir) {
            case Direction::UP:
                bullet.pos.y -= BULLET_SPEED;
                break;
            case Direction::DOWN:
                bullet.pos.y += BULLET_SPEED;
                break;
            case Direction::LEFT:
                bullet.pos.x -= BULLET_SPEED;
                break;
            case Direction::RIGHT:
                bullet.pos.x += BULLET_SPEED;
                break;
            default:
                break;
        }
        bullet.distanceTraveled += BULLET_SPEED;
    }

    // Remove bullets that have traveled beyond their range
    _bullets.erase(
    std::remove_if(_bullets.begin(), _bullets.end(), [](const Bullet& b) {
        return b.distanceTraveled >= 3 * CELL_SIZE;
    }),
    _bullets.end()
);

    // Keep spaceship within bounds (80,80) to (720,520)
    if (_shipPosition.x < START_X || _shipPosition.x > END_X ||
        _shipPosition.y < START_Y || _shipPosition.y > END_Y) {
        _state = GameState::GAME_OVER;
        return;
    }
}

void arcade::Solarfox::detectCollisions()
{
    for (auto& bullet : _bullets) {
        for (auto& powerup : _powerups) {
            if (powerup.collected) continue;

            // Simple collision check (bullet is a point, powerup is a 30x30 box)
            if (bullet.pos.x >= powerup.pos.x - 2 && bullet.pos.x <= powerup.pos.x + 30 &&
                bullet.pos.y >= powerup.pos.y - 2&& bullet.pos.y <= powerup.pos.y + 30) {
                powerup.collected = true;
                _score += 10;
            }
        }
    }
}

void arcade::Solarfox::handleSpaceshipDirection(Key key)
{
        switch (key) {
        case Key::UP:
        case Key::Z:
            _shipDirection = Direction::UP;
            break;
        case Key::DOWN:
        case Key::S:
            _shipDirection = Direction::DOWN;
            break;
        case Key::LEFT:
        case Key::Q:

            break;
        case Key::RIGHT:
        case Key::D:

            break;
        default:
            break;
    }
    // if ((key == Key::UP || key == Key::Z) && _shipDirection != Direction::DOWN) {
    //     _shipDirection = Direction::UP;
    //     _currentSpritePath = "sprite/spaceship1.png";
    // } else if ((key == Key::DOWN || key == Key::S) && _shipDirection != Direction::UP) {
    //     _shipDirection = Direction::DOWN;
    //     _currentSpritePath = "sprite/spaceship3.png";
    // } else if ((key == Key::LEFT || key == Key::Q) && _shipDirection != Direction::RIGHT) {
    //     _shipDirection = Direction::LEFT;
    //     _currentSpritePath = "sprite/spaceship4.png";
    // } else if ((key == Key::RIGHT || key == Key::D) && _shipDirection != Direction::LEFT) {
    //     _shipDirection = Direction::RIGHT;
    //     _currentSpritePath = "sprite/spaceship2.png";
    // }
        if ((key == Key::UP || key == Key::Z)) {
        _shipDirection = Direction::UP;
        _currentSpritePath = "sprite/spaceship1.png";
    } else if ((key == Key::DOWN || key == Key::S)) {
        _shipDirection = Direction::DOWN;
        _currentSpritePath = "sprite/spaceship3.png";
    } else if ((key == Key::LEFT || key == Key::Q)) {
        _shipDirection = Direction::LEFT;
        _currentSpritePath = "sprite/spaceship4.png";
    } else if ((key == Key::RIGHT || key == Key::D)) {
        _shipDirection = Direction::RIGHT;
        _currentSpritePath = "sprite/spaceship2.png";
    }
}

void arcade::Solarfox::handleInput(Key key)
{
    if (key == Key::P) {
        if (_state == GameState::RUNNING)
            pause();
        else if (_state == GameState::PAUSED)
            resume();
        return;
    } else if (key == Key::SPACE) {
        Bullet newBullet;
        newBullet.pos = _shipPosition;
        newBullet.dir = _shipDirection;
        _bullets.push_back(newBullet);
    }

    handleSpaceshipDirection(key);
}

void arcade::Solarfox::handleInput(MouseEvent mouseEvent)
{
    (void)mouseEvent;
}

void arcade::Solarfox::initPowerups()
{
    _powerups.clear();

    for (int y = START_Y; y < END_Y; y += CELL_SIZE) {
        for (int x = START_X; x < END_X; x += CELL_SIZE) {
            Powerup p;
            p.pos = {static_cast<float>(x),
                     static_cast<float>(y)};
            // if (_level == 1) {
            //     if ((x >= (CELL_SIZE * 4) && x <= (CELL_SIZE * 7)) || (y >= (CELL_SIZE * 3) && y <= (CELL_SIZE * 5)))
            //         p.collected = false;
            //     else
            //         p.collected = true;
            // }
            p.collected = false;
            _powerups.push_back(p);
        }
    }
}

void arcade::Solarfox::restart()
{
    int midX = _context.width / 2;
    int midY = _context.height / 2;

    _state = GameState::RUNNING;
    _score = 0;

    _currentSpritePath = "sprite/spaceship2.png";
    _shipPosition = {static_cast<float>(midX), static_cast<float>(midY)};
    _shipDirection = Direction::NONE;
    _bullets.clear();
    _powerups.clear();
    _level = 1;

    _timeSinceLastMove = static_cast<float>(0.0);
    _moveInterval = static_cast<float>(MOVE_INTERVAL);
    initPowerups();
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::Solarfox();
    }
}
