/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade
*/

#ifndef ARCADE_HPP
#define ARCADE_HPP

#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"

namespace arcade {
    class Arcade {
        public:
            Arcade(int ac, char* av[]);
            ~Arcade() = default;

            int run();
        private:
            void printUsage(const std::string& programName) const;
            DLLoader<IDisplayModule> _graphicLoader;
            IDisplayModule* _graphic;
            GameState _gameState;
    };
}

#endif /* !ARCADE_HPP */
