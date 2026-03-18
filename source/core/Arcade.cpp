// Arcade.cpp
#include "Arcade.hpp"
#include <stdexcept>
#include <iostream>

arcade::Arcade::Arcade(int ac, char* av[])
    : _graphicLoader(ac == 2 ? av[1] : ""),
    _graphic(nullptr),
    _gameState(GameState::MENU)
{
    if (ac != 2) {
        printUsage(av[0]);
        throw std::invalid_argument("Invalid number of arguments.");
    }

    _graphic = _graphicLoader.getInstance();

    if (!_graphic)
        throw std::runtime_error("Failed to load graphic library: " + std::string(av[1]));
}

int arcade::Arcade::run()
{
    printf("running ...\n");
    return 0;
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