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
#include <filesystem>
#include <fstream>

static const std::string GAMENAME = "ArcadeMenu";
static const std::string EMPTY = "";

arcade::ArcadeMenu::ArcadeMenu()
    : AGameModule(GAMENAME, GameState::MENU, RenderContext(800, 600, CoordinateSpace::PIXEL)),
      _currentSection(CurrentChoice::ONGRAPHIC),
      _validatedSection(CurrentChoice::ONGRAPHIC),
      _hasValidatedSelection(false),
      _displayIdx(0),
      _gameIdx(0),
      _needsUpdate(true),
      _playerName("Guest"),
      _isInPlayerBox(false)
{
    init();
}

void arcade::ArcadeMenu::setDisplayPaths(const std::vector<std::string>& paths) {
    _displayPaths = paths;
    _needsUpdate = true;
}

void arcade::ArcadeMenu::setGamePaths(const std::vector<std::string>& paths) {
    _gamePaths = paths;
    _needsUpdate = true;
}

void arcade::ArcadeMenu::setDisplayIdx(const int idx)
{
    _currentDisplayIdx = idx;
    _needsUpdate = true;
}

void arcade::ArcadeMenu::restart()
{
    _state = GameState::RUNNING;
    _gameIdx = 0;
    _displayIdx = 0;
    _currentSection = CurrentChoice::ONGRAPHIC;
    _validatedSection = CurrentChoice::ONGRAPHIC;
    _hasValidatedSelection = false;
    _needsUpdate = true;
}

void arcade::ArcadeMenu::handleInput(Key key)
{
    _needsUpdate = true;
    if (_isInPlayerBox) {
        handlePlayerNameInput(key);
        return;
    }
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
        case Key::N:
            _isInPlayerBox = true;
            break;
        default:
            break;
    }
}

void arcade::ArcadeMenu::handleInput([[maybe_unused]] MouseEvent mouseEvent) {}

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

void arcade::ArcadeMenu::isResized()
{
    static float lastWidth = -1;
    static float lastHeight = -1;

    if (lastWidth != _context.width || lastHeight != _context.height) {
        lastWidth = _context.width;
        lastHeight = _context.height;
        _needsUpdate = true;
    }
}

void arcade::ArcadeMenu::drawTitle(float midX)
{
    _uiText.push_back(Text(
        "Start Game",
        midX,
        65,
        Anchor::CENTER,
        Colors::YELLOW,
        40
    ));
}

void arcade::ArcadeMenu::drawGraphicsSection(float leftBarX, float ColY, float midY)
{
    _uiText.push_back(Text(
        "Graphics",
        leftBarX + 35,
        ColY,
        Anchor::MIDDLE_LEFT,
        Colors::CYAN,
        30
    ));

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
    selector.spritePath = "sprite/menu/arrow3.png";
    selector.anchor = Anchor::CENTER;
    selector.size = {65, 65};

    for (size_t i = 0; i < _displayPaths.size(); i++) {
        Color color = Colors::WHITE;
        if (i == static_cast<size_t>(_currentDisplayIdx))
            color = Colors::GREEN;
        if (_currentSection == CurrentChoice::ONGRAPHIC && i == static_cast<size_t>(_displayIdx) && _isInPlayerBox == false) {
            color = Colors::RED;
            selector.pos = {leftBarX + 20, static_cast<float>(y)};
            _entities.push_back(selector);
        }
        _uiText.push_back(Text(
            _displayPaths[i],
            leftBarX + 40,
            y,
            Anchor::MIDDLE_LEFT,
            color,
            10
        ));
        y += 40;
    }
}

void arcade::ArcadeMenu::drawGamesSection(float rightBarX, float ColY, float midY)
{
    _uiText.push_back(Text(
        "Games",
        rightBarX + 35,
        ColY,
        Anchor::MIDDLE_LEFT,
        Colors::CYAN,
        30
    ));

    Entity gameLineBar;
    gameLineBar.pos = {rightBarX, midY};
    gameLineBar.anchor = Anchor::CENTER;
    gameLineBar.size = {2.0f, 320.0f};
    gameLineBar.character = '|';
    gameLineBar.color = Colors::WHITE;
    gameLineBar.spritePath = "";
    _entities.push_back(gameLineBar);

    int y = 200;
    Entity selector;
    selector.color = Colors::RED;
    selector.spritePath = "sprite/menu/arrow3.png";
    selector.anchor = Anchor::CENTER;
    selector.size = {65, 65};

    for (size_t i = 0; i < _gamePaths.size(); i++) {
        Color color = Colors::WHITE;
        if (_currentSection == CurrentChoice::ONGAME && i == static_cast<size_t>(_gameIdx) && _isInPlayerBox == false) {
            color = Colors::RED;
            selector.pos = {rightBarX + 20, static_cast<float>(y)};
            _entities.push_back(selector);
        }
        _uiText.push_back(Text(
            _gamePaths[i],
            rightBarX + 40,
            y,
            Anchor::MIDDLE_LEFT,
            color,
            10
        ));
        y += 40;
    }
}

void arcade::ArcadeMenu::drawPlayerNameBox(float midX)
{
    _uiText.push_back(Text(
        "Press N to enter your name",
        midX,
        static_cast<float>(_context.height - 80),
        Anchor::CENTER,
        Colors::YELLOW,
        15
    ));

    Entity playerNameBoxTop;
    playerNameBoxTop.pos = {midX, static_cast<float>(_context.height - 50)};
    playerNameBoxTop.anchor = Anchor::CENTER;
    playerNameBoxTop.size = {320, 1};
    playerNameBoxTop.character = '-';
    playerNameBoxTop.spritePath = "sprite/menu/playerNameBox.png";
    _entities.push_back(playerNameBoxTop);

    Entity playerNameBoxBottom;
    playerNameBoxBottom.pos = {midX, static_cast<float>(_context.height - 30)};
    playerNameBoxBottom.anchor = Anchor::CENTER;
    playerNameBoxBottom.size = {320, 1};
    playerNameBoxBottom.character = '-';
    playerNameBoxBottom.spritePath = "sprite/menu/playerNameBox.png";
    _entities.push_back(playerNameBoxBottom);

    Entity playerNameBoxLeft;
    playerNameBoxLeft.pos = {midX - 160, static_cast<float>(_context.height - 40)};
    playerNameBoxLeft.anchor = Anchor::CENTER;
    playerNameBoxLeft.size = {1, 20};
    playerNameBoxLeft.character = '|';
    playerNameBoxLeft.spritePath = "sprite/menu/playerNameBox.png";
    _entities.push_back(playerNameBoxLeft);

    Entity playerNameBoxRight;
    playerNameBoxRight.pos = {midX + 160, static_cast<float>(_context.height - 40)};
    playerNameBoxRight.anchor = Anchor::CENTER;
    playerNameBoxRight.size = {1, 20};
    playerNameBoxRight.character = '|';
    playerNameBoxRight.spritePath = "sprite/menu/playerNameBox.png";
    _entities.push_back(playerNameBoxRight);

    Color nameColor = _isInPlayerBox ? Colors::YELLOW : Colors::WHITE;
    _uiText.push_back(Text(
        _playerName,
        midX,
        static_cast<float>(_context.height - 40),
        Anchor::CENTER,
        nameColor,
        12
    ));
}

void arcade::ArcadeMenu::update([[maybe_unused]] float elapsedTime)
{
    isResized();

    if (!_needsUpdate)
        return;

    _needsUpdate = false;

    float midX = _context.width / 2.0f;
    float midY = _context.height / 2.0f;

    _uiText.clear();
    _entities.clear();

    float leftColX = (midX / 2.0f);
    float rightColX = midX + (midX / 2.0f);
    float leftBarX = leftColX / 2.0f;
    float rightBarX = rightColX - 150.0f;
    float ColY = midY - 150.0f;

    drawTitle(midX);
    drawGraphicsSection(leftBarX, ColY, midY);
    drawGamesSection(rightBarX, ColY, midY);
    drawPlayerNameBox(midX);
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

const std::string& arcade::ArcadeMenu::getPlayerName() const { return _playerName; }

void arcade::ArcadeMenu::setPlayerName(const std::string& name) { _playerName = name; }

void arcade::ArcadeMenu::handlePlayerNameInput(Key key)
{
    std::map<Key, char> keyNames = {
        {Key::A, 'A'}, {Key::B, 'B'}, {Key::C, 'C'}, {Key::D, 'D'}, {Key::E, 'E'},
        {Key::F, 'F'}, {Key::G, 'G'}, {Key::H, 'H'}, {Key::I, 'I'}, {Key::J, 'J'},
        {Key::K, 'K'}, {Key::L, 'L'}, {Key::M, 'M'}, {Key::N, 'N'}, {Key::O, 'O'},
        {Key::P, 'P'}, {Key::Q, 'Q'}, {Key::R, 'R'}, {Key::S, 'S'}, {Key::T, 'T'},
        {Key::U, 'U'}, {Key::V, 'V'}, {Key::W, 'W'}, {Key::X, 'X'}, {Key::Y, 'Y'},
        {Key::Z, 'Z'},
        {Key::NUM_0, '0'}, {Key::NUM_1, '1'}, {Key::NUM_2, '2'}, {Key::NUM_3, '3'},
        {Key::NUM_4, '4'}, {Key::NUM_5, '5'}, {Key::NUM_6, '6'}, {Key::NUM_7, '7'},
        {Key::NUM_8, '8'}, {Key::NUM_9, '9'}
    };

    if (_playerName == "Guest")
            _playerName = "";
    if (key == Key::BACKSPACE && !_playerName.empty())
        _playerName.pop_back();
    else if (key >= Key::A && key <= Key::Z)
        _playerName += keyNames[key];
    else if (key >= Key::NUM_0 && key <= Key::NUM_9)
        _playerName += keyNames[key];
    else if (key == Key::ENTER) {
        _isInPlayerBox = false;
        if (_playerName.empty()) _playerName = "Guest";
    }
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::ArcadeMenu();
    }
}
