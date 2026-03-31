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
#include <cstddef>

static const std::string GAMENAME = "ArcadeMenu";
static const std::string EMPTY = "";

arcade::ArcadeMenu::ArcadeMenu()
    : AGameModule(GAMENAME, GameState::MENU, RenderContext(800, 600, CoordinateSpace::PIXEL)),
      _currentSection(CurrentChoice::ONGRAPHIC),
      _validatedSection(CurrentChoice::ONGRAPHIC),
      _hasValidatedSelection(false),
      _displayIdx(0),
      _gameIdx(0)
{
    init();
}

void arcade::ArcadeMenu::setDisplayPaths(const std::vector<std::string>& paths) { _displayPaths = paths; }

void arcade::ArcadeMenu::setGamePaths(const std::vector<std::string>& paths) { _gamePaths = paths; }

void arcade::ArcadeMenu::setDisplayIdx(const int idx) { _currentDisplayIdx = idx; }

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
        _displayIdx = (_displayIdx - 1 + _displayPaths.size()) % _displayPaths.size();
        if (_displayIdx == _currentDisplayIdx)
             _displayIdx = (_displayIdx - 1 + _displayPaths.size()) % _displayPaths.size();
    } else if (_currentSection == CurrentChoice::ONGAME && !_gamePaths.empty())
        _gameIdx = (_gameIdx - 1 + _gamePaths.size()) % _gamePaths.size();
}

void arcade::ArcadeMenu::downKey()
{
    if (_currentSection == CurrentChoice::ONGRAPHIC && !_displayPaths.empty()) {
        _displayIdx = (_displayIdx + 1) % _displayPaths.size();
        if (_displayIdx == _currentDisplayIdx)
             _displayIdx = (_displayIdx + 1) % _displayPaths.size();
    } else if (_currentSection == CurrentChoice::ONGAME && !_gamePaths.empty())
        _gameIdx = (_gameIdx + 1) % _gamePaths.size();
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

void arcade::ArcadeMenu::update(float elapsedTime)
{
    static float midX = _context.width / 2.0f;
    static float midY = _context.height / 2.0f;

    (void)elapsedTime;
    _uiText.clear();
    _entities.clear();

    /// Title
    _uiText.push_back(Text("Start Game", midX, 65, Anchor::CENTER, Colors::YELLOW, 40, "font/arcadeStyleFont/arcadeStyleFont.ttf"));

    /// Graphics section
    float leftColX = (midX / 2);
    float rightColX = midX + (midX / 2);
    float leftBarX = leftColX / 2 - 40;
    float rightBarX = rightColX - 165;
    float ColY = midY - (150);
    _uiText.push_back(Text("Graphics", leftBarX + 35, ColY, Anchor::MIDDLE_LEFT, Colors::CYAN, 30));

    /// Draw a vertical line separating the columns in the middle
    Entity graphicLineBar;
    graphicLineBar.pos = {leftBarX, midY};
    graphicLineBar.anchor = Anchor::CENTER;
    graphicLineBar.size = {2.0f, 320.0f};
    graphicLineBar.character = '|';
    graphicLineBar.color = Colors::WHITE;
    graphicLineBar.spritePath = "";
    _entities.push_back(graphicLineBar);

    int y = 200;

    Entity selector;
    selector.color = Colors::RED;
    selector.spritePath = "sprite/arrow3.png";
    selector.anchor = Anchor::CENTER;
    selector.size = {65, 65};

    for (size_t i = 0; i < _displayPaths.size(); i++) {
        Color color = Colors::WHITE;
        if (i == static_cast<size_t>(_currentDisplayIdx))
            color = Colors::GREEN;
        if (_currentSection == CurrentChoice::ONGRAPHIC && i == static_cast<size_t>(_displayIdx)) {
            color = Colors::RED;
            selector.pos = {leftBarX + 20, static_cast<float>(y)};
            _entities.push_back(selector);
        }
        _uiText.push_back(Text(_displayPaths[i], leftBarX + 40, y, Anchor::MIDDLE_LEFT, color, 10));
        y += 40;
    }

    /// Games section
    _uiText.push_back(Text("Games", rightBarX + 35, ColY, Anchor::MIDDLE_LEFT, Colors::CYAN, 30));

    Entity gameLineBar;
    gameLineBar.pos = {rightBarX, midY};
    gameLineBar.anchor = Anchor::CENTER;
    gameLineBar.size = {2.0f, 320.0f};
    gameLineBar.character = '|';
    gameLineBar.color = Colors::WHITE;
    gameLineBar.spritePath = "";
    _entities.push_back(gameLineBar);

    y = 200;
    for (size_t i = 0; i < _gamePaths.size(); i++) {
        Color color = Colors::WHITE;
        if (_currentSection == CurrentChoice::ONGAME && i == static_cast<size_t>(_gameIdx)) {
            color = Colors::RED;
            selector.pos = {rightBarX + 20, static_cast<float>(y)};
            _entities.push_back(selector);
        }
        _uiText.push_back(Text(_gamePaths[i], rightBarX + 40, y, Anchor::MIDDLE_LEFT, color, 10));
        y += 40;
    }
}

const std::vector<arcade::Entity>& arcade::ArcadeMenu::getEntities() const { return _entities; }

const std::vector<arcade::Text>& arcade::ArcadeMenu::getUIText() const { return _uiText; }


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
