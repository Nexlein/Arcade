/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

#include "arcade_menu.hpp"

static const std::string MENU_NAME = "Menu";

arcade::menu::menu() : AGameModule(MENU_NAME) {}

void arcade::menu::init()
{
    _gameState = GameState::MENU;
}
