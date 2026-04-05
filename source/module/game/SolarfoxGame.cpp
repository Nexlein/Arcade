/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SolarfoxGame
*/

#include "SolarfoxGame.hpp"
#include "AGameModule.hpp"
#include "IDisplayModule.hpp"
#include <algorithm>

const std::string GAMENAME = "Solarfox";
const float MOVE_INTERVAL = 0.0167f;
const float SPACESHIP_SPEED = 5.0f;
const float BULLET_SPEED = 16.0f;
const float ENEMY_FIRE_RATE = 3.0f;
const float ENEMY_BULLET_SPEED = 7.0f;

const int CELL_SIZE = 60;
const int START_X = 200;
const int START_Y = 100;
const int END_X = 600;
const int END_Y = 500;

arcade::Solarfox::Solarfox()
    : AGameModule(GAMENAME, GameState::RUNNING, RenderContext(800, 600, CoordinateSpace::PIXEL))
{ init(); }

// ajouter des sons.
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
    // Game background
    Entity background;
    background.pos = {0, 0};
    background.size = {800, 600};
    background.spritePath = "sprite/solarfox/solarfox_bg.png";
    _entities.push_back(background);


    // Bordures de la zone walkable
    // Entity borderTop, borderBottom, borderLeft, borderRight;

    // borderTop.pos = {START_X, START_Y};
    // borderTop.size = {400, 2};
    // borderTop.color = Colors::RED;

    // borderBottom.pos = {START_X, END_Y};
    // borderBottom.size = {400, 2};
    // borderBottom.color = Colors::RED;

    // borderLeft.pos = {START_X, START_Y};
    // borderLeft.size = {2, 400};
    // borderLeft.color = Colors::RED;

    // borderRight.pos = {END_X, START_Y};
    // borderRight.size = {2, 400};
    // borderRight.color = Colors::RED;

    // _entities.push_back(borderTop);
    // _entities.push_back(borderBottom);
    // _entities.push_back(borderLeft);
    // _entities.push_back(borderRight);

    for (const auto& enemy : _enemies) {
        Entity enemyEntity;
        enemyEntity.pos = enemy.pos;
        enemyEntity.size = {40, 40};
        enemyEntity.anchor = enemy.anchor;
        enemyEntity.character = 'E';
        enemyEntity.color = Colors::MAGENTA;
        enemyEntity.spritePath = enemy.spritePath;
        _entities.push_back(enemyEntity);
    }

    for (const auto& bullet : _bullets) {
        Entity bulletEntity;
        bulletEntity.pos = bullet.pos;
        bulletEntity.anchor = Anchor::CENTER;
        bulletEntity.size = { 25,25};
        bulletEntity.character = '*';
        bulletEntity.color = Colors::YELLOW;
        bulletEntity.spritePath = "sprite/solarfox/bullet.png";
        _entities.push_back(bulletEntity);
    }

    for (const auto& eb : _enemyBullets) {
        Entity ebEntity;
        ebEntity.pos = eb.pos;
        ebEntity.anchor = Anchor::CENTER;
        ebEntity.size = {20, 20};
        ebEntity.character = 'o';
        ebEntity.color = Colors::RED;
        ebEntity.spritePath = "sprite/solarfox/fireball.png";
        _entities.push_back(ebEntity);
    }

    for (const auto& powerup : _powerups) {
        if (powerup.collected) continue;

        Entity powerupEntity;
        powerupEntity.pos = powerup.pos;
        powerupEntity.size = {30, 30};
        powerupEntity.character = 'P';
        powerupEntity.color = Colors::GREEN;
        powerupEntity.spritePath = "sprite/solarfox/diamond.png";
        _entities.push_back(powerupEntity);
    }

    _ship.pos = _shipPosition;
    _ship.anchor = Anchor::CENTER;
    _ship.size = {55, 55};
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
    case Direction::UP:    _shipPosition.y -= _shipSpeed; break;
    case Direction::DOWN:  _shipPosition.y += _shipSpeed; break;
    case Direction::LEFT:  _shipPosition.x -= _shipSpeed; break;
    case Direction::RIGHT: _shipPosition.x += _shipSpeed; break;
    case Direction::NONE: return;
    }

    for (auto& bullet : _bullets) {
        switch (bullet.dir) {
        case Direction::UP: bullet.pos.y -= BULLET_SPEED;
            break;
        case Direction::DOWN: bullet.pos.y += BULLET_SPEED;
            break;
        case Direction::LEFT: bullet.pos.x -= BULLET_SPEED;
            break;
        case Direction::RIGHT: bullet.pos.x += BULLET_SPEED;
            break;
        default: break;
        }
        bullet.distanceTraveled += BULLET_SPEED;
    }

    for (auto& enemy : _enemies) {
        switch (enemy.dir) {
            case Direction::UP:
                enemy.pos.y -= SPACESHIP_SPEED / 2;
                break;
            case Direction::DOWN:
                enemy.pos.y += SPACESHIP_SPEED / 2;
                break;
            case Direction::LEFT:
                enemy.pos.x -= SPACESHIP_SPEED / 2;
                break;
            case Direction::RIGHT:
                enemy.pos.x += SPACESHIP_SPEED / 2;
                break;
            default:
                break;
        }
    }

    // Mise à jour timers et spawn des tirs ennemis
    for (auto& enemy : _enemies) {
        enemy.timeSinceLastShot += _moveInterval;
        if (enemy.timeSinceLastShot >= _enemyFireRate) {
            Bullet eb;
            eb.pos = enemy.pos;
            eb.dir = enemy.shotDir;
            _enemyBullets.push_back(eb);
            enemy.timeSinceLastShot = 0.0f;
        }
    }

    // Déplacement des tirs ennemis
    for (auto& eb : _enemyBullets) {
        switch (eb.dir) {
            case Direction::UP:    eb.pos.y -= _bulletSpeed; break;
            case Direction::DOWN:  eb.pos.y += _bulletSpeed; break;
            case Direction::LEFT:  eb.pos.x -= _bulletSpeed; break;
            case Direction::RIGHT: eb.pos.x += _bulletSpeed; break;
            default: break;
        }
    }

    // Suppression si hors bounds
    _enemyBullets.erase(
        std::remove_if(_enemyBullets.begin(), _enemyBullets.end(), [](const Bullet& eb) {
            return eb.pos.x < START_X || eb.pos.x > END_X ||
                eb.pos.y < START_Y || eb.pos.y > END_Y;
        }),
        _enemyBullets.end()
    );


    if (_enemies[0].pos.x >= END_X) _enemies[0].dir = Direction::LEFT;
    else if (_enemies[0].pos.x <= START_X + 30) _enemies[0].dir = Direction::RIGHT;

    if (_enemies[1].pos.y >= END_Y) _enemies[1].dir = Direction::UP;
    else if (_enemies[1].pos.y <= START_Y + 30) _enemies[1].dir = Direction::DOWN;

    if (_enemies[2].pos.x >= END_X) _enemies[2].dir = Direction::LEFT;
    else if (_enemies[2].pos.x <= START_X + 30) _enemies[2].dir = Direction::RIGHT;

    if (_enemies[3].pos.y >= END_Y) _enemies[3].dir = Direction::UP;
    else if (_enemies[3].pos.y <= START_Y + 30) _enemies[3].dir = Direction::DOWN;

    // Remove bullets that have traveled beyond their range
    _bullets.erase(
    std::remove_if(_bullets.begin(), _bullets.end(), [](const Bullet& b) {
        return b.distanceTraveled >= 2 * CELL_SIZE;
    }),
    _bullets.end()
);

    // Keep spaceship within bounds (200,100) to (400,400)
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
                bullet.pos.y >= powerup.pos.y - 2 && bullet.pos.y <= powerup.pos.y + 30) {
                powerup.collected = true;
                _score += 10;
            }
        }
    }

    // Tir ennemi vs vaisseau
    for (const auto& eb : _enemyBullets) {
        const float SHIP_HALF = 25.0f;
        if (eb.pos.x >= _shipPosition.x - SHIP_HALF && eb.pos.x <= _shipPosition.x + SHIP_HALF &&
            eb.pos.y >= _shipPosition.y - SHIP_HALF && eb.pos.y <= _shipPosition.y + SHIP_HALF) {
            _state = GameState::GAME_OVER;
            return;
        }
    }

    // Tir joueur vs tir ennemi
    for (auto& bullet : _bullets) {
        _enemyBullets.erase(
            std::remove_if(_enemyBullets.begin(), _enemyBullets.end(), [&](const Bullet& eb) {
                return std::abs(bullet.pos.x - eb.pos.x) <= 8.0f &&
                    std::abs(bullet.pos.y - eb.pos.y) <= 8.0f;
            }),
            _enemyBullets.end()
        );
    }

    // Passage au niveau suivant si tous les powerups sont collectés
    bool allCollected = std::all_of(_powerups.begin(), _powerups.end(),
        [](const Powerup& p) { return p.collected; });
    if (allCollected && !_powerups.empty())
        nextLevel();
}

void arcade::Solarfox::nextLevel()
{
    _level++;
    _bullets.clear();
    _enemyBullets.clear();
    _currentSpritePath = "sprite/solarfox/ship/spaceship2.png";
    _shipDirection = Direction::NONE;
    _shipPosition = {static_cast<float>(_context.width / 2.0f),
                     static_cast<float>(_context.height / 2.0f)};
    _shipDirection = Direction::NONE;

    _shipSpeed     = SPACESHIP_SPEED + (_level - 1) * 0.6f;   // +0.4 px/tick par niveau
    _bulletSpeed   = BULLET_SPEED    + (_level - 1) * 0.3f;
    _enemyFireRate = std::max(0.8f, ENEMY_FIRE_RATE - (_level - 1) * 0.10f);
    // _moveInterval reste MOVE_INTERVAL, on ne touche plus à ça

    initPowerups();
    initEnemies();
}

void arcade::Solarfox::handleSpaceshipDirection(Key key)
{
    if ((key == Key::UP || key == Key::Z) && _shipDirection != Direction::DOWN) {
        _shipDirection = Direction::UP;
        _currentSpritePath = "sprite/solarfox/ship/spaceship1.png";
    } else if ((key == Key::DOWN || key == Key::S) && _shipDirection != Direction::UP) {
        _shipDirection = Direction::DOWN;
        _currentSpritePath = "sprite/solarfox/ship/spaceship3.png";
    } else if ((key == Key::LEFT || key == Key::Q) && _shipDirection != Direction::RIGHT) {
        _shipDirection = Direction::LEFT;
        _currentSpritePath = "sprite/solarfox/ship/spaceship4.png";
    } else if ((key == Key::RIGHT || key == Key::D) && _shipDirection != Direction::LEFT) {
        _shipDirection = Direction::RIGHT;
        _currentSpritePath = "sprite/solarfox/ship/spaceship2.png";
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

    std::vector<Position> cells;
    for (int y = START_Y; y < END_Y; y += CELL_SIZE)
        for (int x = START_X; x < END_X; x += CELL_SIZE)
            cells.push_back({static_cast<float>(x), static_cast<float>(y)});

    std::shuffle(cells.begin(), cells.end(), _rng);

    int count = std::min(5 + (_level - 1) * 3, static_cast<int>(cells.size()));
    for (int i = 0; i < count; i++)
        _powerups.push_back({cells[i], false});
}

void arcade::Solarfox::initEnemies()
{
    _enemies[0] = {{START_X + 30, START_Y}, Direction::RIGHT, Direction::DOWN,  0.0f,                    "sprite/solarfox/enemy/enemy1.png", Anchor::BOTTOM_RIGHT};
    _enemies[1] = {{END_X, START_Y},        Direction::DOWN,  Direction::LEFT,  _enemyFireRate * 0.25f,  "sprite/solarfox/enemy/enemy2.png", Anchor::BOTTOM_LEFT};
    _enemies[2] = {{END_X / 2.0f, END_Y},   Direction::RIGHT, Direction::UP,   _enemyFireRate * 0.5f,   "sprite/solarfox/enemy/enemy3.png", Anchor::TOP_RIGHT};
    _enemies[3] = {{START_X, END_Y / 2.0f}, Direction::DOWN,  Direction::RIGHT, _enemyFireRate * 0.75f,  "sprite/solarfox/enemy/enemy4.png", Anchor::BOTTOM_RIGHT};

}

void arcade::Solarfox::restart()
{
    int midX = _context.width / 2;
    int midY = _context.height / 2;

    _state = GameState::RUNNING;
    _score = 0;

    _currentSpritePath = "sprite/solarfox/ship/spaceship2.png";
    _shipPosition = {static_cast<float>(midX), static_cast<float>(midY)};
    _shipDirection = Direction::NONE;
    _bullets.clear();
    _powerups.clear();
    _enemyBullets.clear();
    _level = 1;
    _enemyFireRate = ENEMY_FIRE_RATE;
    _rng = std::mt19937(std::random_device{}());

    _timeSinceLastMove = static_cast<float>(0.0);
    _shipSpeed   = SPACESHIP_SPEED;
    _bulletSpeed = ENEMY_BULLET_SPEED;
    _moveInterval = MOVE_INTERVAL;
    initPowerups();
    initEnemies();
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::Solarfox();
    }
}
