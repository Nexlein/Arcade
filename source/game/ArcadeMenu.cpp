/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

#include "ArcadeMenu.hpp"
#include "IDisplayModule.hpp"

static const std::string GAMENAME = "ArcadeMenu";

// faudrait que le getRender du snake définisse un static const plustot que reconstruire a chaque fois.
// window size peu etre a revoir?

arcade::ArcadeMenu::ArcadeMenu(std::vector<std::string> displayPath, std::vector<std::string> gamePath)
    : AGameModule(GAMENAME, GameState::MENU, 200, 300),
    _displayPath(displayPath),
    _gamePath(gamePath),
    _currentIdx(CurrentChoice::ONGRAPHIC) { init(); }

void arcade::ArcadeMenu::restart()
{
    _state = GameState::RUNNING;
    int x = 10;
    int y = 5;

    for (const auto display : _displayPath) {
        arcade::Text newText( display, x, y, Colors::WHITE, 30);
        _uiText.push_back(newText);
        y += 20;
    }
    x = 200;
    y = 5;
    for (const auto display : _gamePath) {
        arcade::Text newText( display, x, y, Colors::WHITE, 30);
        _uiText.push_back(newText);
        y += 20;
    }
    _gameIdx = 0;
    _displayIdx = 0;
}

void arcade::ArcadeMenu::handleInput(Key key)
{
    switch (key) {
        case Key::UP:
            upKey();
            break;
        case Key::DOWN:
            downKey();
            break;
        case Key::LEFT:
            switchChoice(key);
            break;
        case Key::RIGHT:
            switchChoice(key);
            break;
        default: break;
    }
}

void arcade::ArcadeMenu::upKey()
{
    if (_currentIdx == CurrentChoice::ONGRAPHIC) {
        _displayIdx -= 1;
        if (_displayIdx < 0)
            _displayIdx = (_displayPath.size() - 1);
    } else if (_currentIdx == CurrentChoice::ONGAME) {
        _gameIdx -= 1;
        if (_gameIdx < 0)
            _gameIdx = (_gamePath.size() - 1);
    }
}

void arcade::ArcadeMenu::downKey()
{
    if (_currentIdx == CurrentChoice::ONGRAPHIC) {
        _displayIdx  = (_displayIdx + 1) % _displayPath.size();
    } else if (_currentIdx == CurrentChoice::ONGAME) {
        _gameIdx  = (_gameIdx + 1) % _gamePath.size();
    }
}

void arcade::ArcadeMenu::switchChoice(const Key& key)
{
    key == Key::LEFT ?
    _currentIdx = CurrentChoice::ONGRAPHIC :
    _currentIdx = CurrentChoice::ONGAME;
}

void arcade::ArcadeMenu::update(float deltaTime) {}

const std::vector<arcade::Entity>& arcade::ArcadeMenu::getEntities() const {}

const std::vector<arcade::Text>& arcade::ArcadeMenu::getUIText() const { return _uiText; }

arcade::RenderContext arcade::ArcadeMenu::getRenderContext() const
{
    static const RenderContext renderer(_width, _height, CoordinateSpace::PIXEL);
    return renderer;
}

