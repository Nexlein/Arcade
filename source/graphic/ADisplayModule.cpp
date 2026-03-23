/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** ADisplayModule
*/

#include "ADisplayModule.hpp"

arcade::ADisplayModule::ADisplayModule(std::string name) : _name(name) {}

arcade::ModuleType arcade::ADisplayModule::getType() const
{
    return ModuleType::DISPLAY;
}

const std::string& arcade::ADisplayModule::getName() const
{
    return _name;
}
