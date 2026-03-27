/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** AGameModule
*/

#include "AGameModule.hpp"
#include "IDisplayModule.hpp"

arcade::AGameModule::AGameModule(std::string name, GameState initialState, RenderContext context)
    : _name(name), _state(initialState), _context(context), _score(0)
{}

arcade::RenderContext arcade::AGameModule::getRenderContext() const { return _context; }

arcade::ModuleType arcade::AGameModule::getType() const { return ModuleType::GAME; }

const std::string& arcade::AGameModule::getName() const { return _name; }

arcade::GameState arcade::AGameModule::getState() const { return _state; }

int arcade::AGameModule::getScore() const { return _score; }

void arcade::AGameModule::stop() {}

void arcade::AGameModule::pause()
{
    if (_state == GameState::RUNNING) _state = GameState::PAUSED;
}

void arcade::AGameModule::resume()
{
    if (_state == GameState::PAUSED) _state = GameState::RUNNING;
}

void arcade::AGameModule::init() { restart(); }

void arcade::AGameModule::appendCommonUITexts(std::vector<arcade::Text>& uiTexts) const
{
    float yPos = static_cast<float>(_context.height);

    // Bottom left summary
    uiTexts.push_back(Text("[R] Restart  [P] Pause  [M] Menu", 1, yPos, Anchor::BOTTOM_LEFT, Colors::WHITE, 16));

    if (_state == GameState::PAUSED) {
        uiTexts.push_back(Text("PAUSED", static_cast<float>(_context.width) / 2, static_cast<float>(_context.height) / 2, Anchor::CENTER, Colors::YELLOW, 30));
    }
}

