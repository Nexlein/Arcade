/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** ArcadeMenu
*/

/// @file ArcadeMenu.cpp
/// @brief Implementation of the ArcadeMenu class, which provides a menu interface for selecting
/// games and graphics libraries in the arcade application.

#include "ArcadeMenu.hpp"

#include "IDisplayModule.hpp"
#include <chrono>
#include <cstddef>

static const std::string GAMENAME = "ArcadeMenu";
static const std::string EMPTY = "";

arcade::ArcadeMenu::ArcadeMenu()
    : AGameModule(GAMENAME, GameState::MENU),
      _currentSection(CurrentChoice::ONGRAPHIC),
      _validatedSection(CurrentChoice::ONGRAPHIC),
      _hasValidatedSelection(false),
      _displayIdx(0),
      _gameIdx(0)
{
    init();
}

void arcade::ArcadeMenu::setDisplayPaths(const std::vector<std::string>& paths)
{
    _displayPaths = paths;
}

void arcade::ArcadeMenu::setGamePaths(const std::vector<std::string>& paths) { _gamePaths = paths; }

void arcade::ArcadeMenu::restart()
{
    _state = GameState::RUNNING;
    _gameIdx = 0;
    _displayIdx = 0;
    _currentSection = CurrentChoice::ONGRAPHIC;
    _validatedSection = CurrentChoice::ONGRAPHIC;
    _hasValidatedSelection = false;
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
        case Key::RIGHT:
            switchChoice(key);
            break;
        case Key::ENTER:
            _validatedSection = _currentSection;
            _hasValidatedSelection = true;
            _state = GameState::WON;
            break;
        default:
            break;
    }
}

void arcade::ArcadeMenu::upKey()
{
    if (_currentSection == CurrentChoice::ONGRAPHIC && !_displayPaths.empty()) {
        _displayIdx -= 1;
        if (_displayIdx < 0) _displayIdx = static_cast<int>(_displayPaths.size()) - 1;
    } else if (_currentSection == CurrentChoice::ONGAME && !_gamePaths.empty()) {
        _gameIdx -= 1;
        if (_gameIdx < 0) _gameIdx = static_cast<int>(_gamePaths.size()) - 1;
    }
}

void arcade::ArcadeMenu::downKey()
{
    if (_currentSection == CurrentChoice::ONGRAPHIC && !_displayPaths.empty()) {
        _displayIdx = (_displayIdx + 1) % _displayPaths.size();
    } else if (_currentSection == CurrentChoice::ONGAME && !_gamePaths.empty()) {
        _gameIdx = (_gameIdx + 1) % _gamePaths.size();
    }
}

void arcade::ArcadeMenu::switchChoice(const Key& key)
{
    if (key == Key::LEFT || key == Key::RIGHT) {
        if (_currentSection == CurrentChoice::ONGRAPHIC)
            _currentSection = CurrentChoice::ONGAME;
        else
            _currentSection = CurrentChoice::ONGRAPHIC;
    }
}

void arcade::ArcadeMenu::handleInput(MouseEvent mouseEvent) { (void)mouseEvent; }

// pk Entity dans update?
void arcade::ArcadeMenu::update(float elapsedTime)
{
    static float midX = _width / 2.0f;
    static float midY = _height / 2.0f;

    (void)elapsedTime;
    _uiText.clear();
    _entities.clear();

    /// Title
    _uiText.push_back(Text("Start Game", static_cast<float>(_width) / 2, 70, Anchor::CENTER, Colors::YELLOW, 40, "font/arcadeStyleFont/arcadeStyleFont.ttf"));

    // Background
    // Entity bg;
    // bg.pos = {0, 0};
    // bg.size = {static_cast<float>(_width), static_cast<float>(_height)};
    // bg.color = Colors::WHITE;
    // bg.spritePath = "sprite/beachBg.jpg";
    // _entities.push_back(bg);

    /// Draw a vertical line separating the columns in the middle
    Entity lineBar;
    lineBar.pos = {midX, midY};
    lineBar.anchor = Anchor::CENTER;
    lineBar.size = {2.0f, 320.0f};
    lineBar.character = '|';
    lineBar.color = Colors::WHITE;
    lineBar.spritePath = "";
    _entities.push_back(lineBar);

    /// Graphics section
    float leftColX = midX / 2;
    float ColY = midY - (150);
    _uiText.push_back(Text("Graphics:", leftColX, ColY, Anchor::CENTER, Colors::CYAN, 30));

    int y = 200;
    for (size_t i = 0; i < _displayPaths.size(); i++) {
        Color color = Colors::WHITE;
        if (_currentSection == CurrentChoice::ONGRAPHIC && i == static_cast<size_t>(_displayIdx))
            color = Colors::RED;
        _uiText.push_back(Text(_displayPaths[i], leftColX, y, Anchor::CENTER, color, 15));
        y += 40;
    }

    /// Games section
    float rightColX = midX + (midX / 2);
    _uiText.push_back(Text("Games:", rightColX, ColY, Anchor::CENTER, Colors::CYAN, 30));

    y = 200;
    for (size_t i = 0; i < _gamePaths.size(); i++) {
        Color color = Colors::WHITE;
        if (_currentSection == CurrentChoice::ONGAME && i == static_cast<size_t>(_gameIdx))
            color = Colors::RED;
        _uiText.push_back(Text(_gamePaths[i], rightColX, y, Anchor::CENTER, color, 15));
        y += 40;
    }
}

const std::vector<arcade::Entity>& arcade::ArcadeMenu::getEntities() const { return _entities; }

const std::vector<arcade::Text>& arcade::ArcadeMenu::getUIText() const { return _uiText; }

arcade::RenderContext arcade::ArcadeMenu::getRenderContext() const
{
    static RenderContext context(_width, _height, CoordinateSpace::GRID);
    return context;
}

const std::string& arcade::ArcadeMenu::getSelectedGame() const
{
    if (!_hasValidatedSelection || _validatedSection != CurrentChoice::ONGAME) return EMPTY;
    if (_gameIdx >= 0 && _gameIdx < static_cast<int>(_gamePaths.size()))
        return _gamePaths[_gameIdx];
    return EMPTY;
}

const std::string& arcade::ArcadeMenu::getSelectedGraphic() const
{
    if (!_hasValidatedSelection || _validatedSection != CurrentChoice::ONGRAPHIC) return EMPTY;
    if (_displayIdx >= 0 && _displayIdx < static_cast<int>(_displayPaths.size()))
        return _displayPaths[_displayIdx];
    return EMPTY;
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::ArcadeMenu();
    }
}
