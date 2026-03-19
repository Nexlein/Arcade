/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

#include "arcade_menu.hpp"

arcade::menu::menu()
{
    _name = "Menu";
}

void arcade::menu::init()
{
    _gameState = GameState::MENU;
}
