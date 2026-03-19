/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

#include "ArcadeMenu.hpp"

static const std::string MENU_NAME = "ArcadeMenu";
// 
arcade::ArcadeMenu::ArcadeMenu(std::vector<std::string> displayPath, std::vector<std::string> gamePath)
    : AGameModule(MENU_NAME),
    _displayPath(displayPath),
    _gamePath(gamePath) {}

void arcade::ArcadeMenu::init()
{
    _state = GameState::RUNNING;
}
