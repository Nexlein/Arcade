/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

// Exemple d'utilisation dans ton Core :
// arcade::IGameModule* menuModule = menuLoader->getInstance();
// arcade::ArcadeMenu* menu = dynamic_cast<arcade::ArcadeMenu*>(menuModule);
// 
// if (menu) {
//     menu->setDisplayPaths(myFoundGraphics);
//     menu->setGamePaths(myFoundGames);
// }

#include "ArcadeMenu.hpp"

#include "IDisplayModule.hpp"

static const std::string GAMENAME = "ArcadeMenu";
static const std::string EMPTY = "";

arcade::ArcadeMenu::ArcadeMenu()
    : AGameModule(GAMENAME, GameState::MENU, 50, 50),
      _currentSection(CurrentChoice::ONGRAPHIC),
      _displayIdx(0),
      _gameIdx(0)
{
    init();
}

void arcade::ArcadeMenu::restart()
{
    _state = GameState::RUNNING;
    _gameIdx = 0;
    _displayIdx = 0;
    _currentSection = CurrentChoice::ONGRAPHIC;
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
        case Key::ENTER:
            _state = GameState::WON;
            break;
        default:
            break;
    }
}

void arcade::ArcadeMenu::upKey()
{
    if (_currentSection == CurrentChoice::ONGRAPHIC && !_displayPath.empty()) {
        _displayIdx -= 1;
        if (_displayIdx < 0) _displayIdx = _displayPath.size() - 1;
    } else if (_currentSection == CurrentChoice::ONGAME && !_gamePath.empty()) {
        _gameIdx -= 1;
        if (_gameIdx < 0) _gameIdx = _gamePath.size() - 1;
    }
}

void arcade::ArcadeMenu::downKey()
{
    if (_currentSection == CurrentChoice::ONGRAPHIC && !_displayPath.empty()) {
        _displayIdx = (_displayIdx + 1) % _displayPath.size();
    } else if (_currentSection == CurrentChoice::ONGAME && !_gamePath.empty()) {
        _gameIdx = (_gameIdx + 1) % _gamePath.size();
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

void arcade::ArcadeMenu::update(float elapsedTime)
{
    (void)elapsedTime;
    _uiText.clear();
    _entities.clear();

    /// Title
    _uiText.push_back(Text(
        "Arcade Menu",
        _width / 2,
        2,
        Anchor::CENTER,
        Colors::YELLOW,
        40
    ));

    /// Draw a vertical line separating the columns in the middle
    int midX = _width / 2;
    for (int y = 5; y < _height - 2; y++) {
        Entity linePart;
        linePart.pos = {static_cast<float>(midX), static_cast<float>(y)};
        linePart.character = '|';
        linePart.color = Colors::WHITE;
        _entities.push_back(linePart);
    }

    /// Graphics section
    int leftColX = midX / 2;
    _uiText.push_back(Text(
        "Graphics:",
        leftColX,
        6,
        Anchor::TOP_CENTER,
        Colors::CYAN,
        30
    ));

    int y = 10;
    for (size_t i = 0; i < _displayPath.size(); i++) {
        Color color = Colors::WHITE;
        if (_currentSection == CurrentChoice::ONGRAPHIC && i == static_cast<size_t>(_displayIdx))
            color = Colors::RED;
        _uiText.push_back(Text(
            _displayPath[i],
            leftColX,
            y,
            Anchor::TOP_CENTER,
            color,
            30
        ));
        y += 3;
    }

    /// Games section
    int rightColX = midX + (midX / 2);
    _uiText.push_back(Text(
        "Games:",
        rightColX,
        6,
        Anchor::TOP_CENTER,
        Colors::CYAN,
        30
    ));

    y = 10;
    for (size_t i = 0; i < _gamePath.size(); i++) {
        Color color = Colors::WHITE;
        if (_currentSection == CurrentChoice::ONGAME && i == static_cast<size_t>(_gameIdx))
            color = Colors::RED;
        _uiText.push_back(Text(
            _gamePath[i],
            rightColX,
            y,
            Anchor::TOP_CENTER,
            color,
            30
        ));
        y += 3;
    }
}

const std::vector<arcade::Entity>& arcade::ArcadeMenu::getEntities() const { return _entities; }

const std::vector<arcade::Text>& arcade::ArcadeMenu::getUIText() const { return _uiText; }

arcade::RenderContext arcade::ArcadeMenu::getRenderContext() const
{
    return RenderContext(_width, _height, CoordinateSpace::GRID);
}

const std::string& arcade::ArcadeMenu::getSelectedGame() const
{
    if (_gameIdx >= 0 && _gameIdx < static_cast<int>(_gamePath.size()))
        return _gamePath[_gameIdx];
    return EMPTY;
}

const std::string& arcade::ArcadeMenu::getSelectedGraphic() const
{
    if (_displayIdx >= 0 && _displayIdx < static_cast<int>(_displayPath.size()))
        return _displayPath[_displayIdx];
    return EMPTY;
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::ArcadeMenu();
    }
}
