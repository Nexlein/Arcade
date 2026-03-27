/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** ADisplayModule
*/

/// @file ADisplayModule.cpp
/// @brief Implementation of the ADisplayModule class, an abstract base class for display modules in
/// the Arcade project

#include "ADisplayModule.hpp"

arcade::ADisplayModule::ADisplayModule(std::string name, RenderContext context)
    : _name(name),
      _title(""),
      _context(context),
      _fullScreen(false),
      _currentTime(0),
      _lastTime(0)
{
}

arcade::Key arcade::ADisplayModule::getKey()
{
    if (_keyEvent.empty()) return Key::UNKNOWN;

    Key lastKey = _keyEvent.front();
    _keyEvent.pop();

    return lastKey;
}

arcade::MouseEvent arcade::ADisplayModule::getMouseEvent()
{
    if (_mouseEvent.empty()) return MouseEvent{{0, 0}, Key::UNKNOWN};

    MouseEvent lastMouse = _mouseEvent.front();
    _mouseEvent.pop();

    return lastMouse;
}

// --- Getters ---

arcade::ModuleType arcade::ADisplayModule::getType() const { return ModuleType::DISPLAY; }
const std::string& arcade::ADisplayModule::getName() const { return _name; }
float arcade::ADisplayModule::getDeltaTime() const { return _currentTime - _lastTime; }
int arcade::ADisplayModule::getWidth() const { return _context.width; }
int arcade::ADisplayModule::getHeight() const { return _context.height; }

// --- Setters ---

void arcade::ADisplayModule::setTitle(const std::string& title) { _title = title; }
void arcade::ADisplayModule::setWindowSize(int width, int height)
{
    _context.width = width;
    _context.height = height;
}
void arcade::ADisplayModule::setFullscreen(bool fullscreen) { _fullScreen = fullscreen; }
void arcade::ADisplayModule::setRenderContext(const RenderContext& context) { _context = context; }
