/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade
*/

// Arcade.cpp
#include "Arcade.hpp"
#include <stdexcept>
#include <iostream>
#include <filesystem>

arcade::Arcade::Arcade(int ac, char* av[])
    : _graphicLoader(std::make_unique<DLLoader<IDisplayModule>>(ac == 2 ? av[1] : "")),
    _gameLoader(nullptr),
    _game(nullptr),
    _displayIdx(-1),
    _gameIdx(-1),
    _gameState(GameState::MENU),
    _playerName(""),
    _isRunning(true)
{
    if (ac != 2) {
        printUsage(av[0]);
        throw std::invalid_argument("Invalid number of arguments.");
    }

    try {
        _graphic = _graphicLoader.get()->getInstance();
    } catch (const DLLoader<IDisplayModule>::DLLoaderException& e) {
        throw e.what();
    }
}

int arcade::Arcade::run()
{
    while (_isRunning) {
        switch (_gameState) {
        case GameState::MENU: menuManager();
            break;
        default:
            break;
        }
    }
    return 0;
}

void arcade::Arcade::menuManager()
{
    
}

void arcade::Arcade::loadLibrairies(const std::string& loadPath)
{
    std::unique_ptr<DLLoader<IModule>> loader;
    IModule* mod;

    for (const auto& file : std::filesystem::directory_iterator(loadPath)) {
        if (file.is_regular_file() && file.path().extension() == ".so") {
            loader = std::make_unique<DLLoader<IModule>>(file.path());
            mod = loader.get()->getInstance();
            printf("module_name:%s, type: %d\n\n", mod->getName(), int(mod->getType()));
            // en fonction du type trouvé -> stocker dans la liste correspondante.
        }
    }
}

void arcade::Arcade::printUsage(const std::string& programName) const
{
    std::cerr
        << "\n"
        << "   █████╗ ██████╗  ██████╗ █████╗ ██████╗ ███████╗\n"
        << "  ██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝\n"
        << "  ███████║██████╔╝██║     ███████║██║  ██║█████╗  \n"
        << "  ██╔══██║██╔══██╗██║     ██╔══██║██║  ██║██╔══╝  \n"
        << "  ██║  ██║██║  ██║╚██████╗██║  ██║██████╔╝███████╗\n"
        << "  ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚═════╝ ╚══════╝\n"
        << "\n"
        << "  THE EPITECH ARCADE EMULATOR — v1.0\n"
        << "\n"
        << "  \033[31mERROR  \033[0mInvalid number of arguments.\n"
        << "\n"
        << "  \033[90mUSAGE\033[0m\n"
        << "    " << programName << " \033[33m<graphic_library>\033[0m\n"
        << "\n"
        << "  \033[90mEXAMPLES\033[0m\n"
        << "    " << programName << " \033[33m./lib/arcade_ncurses.so\033[0m\n"
        << "    " << programName << " \033[33m./lib/arcade_sdl2.so\033[0m\n"
        << "\n";
}
