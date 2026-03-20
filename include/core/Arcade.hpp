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
            void loadLibrairies(const std::string& loadPath = "lib");

            void menuManager();

            std::unique_ptr<DLLoader<IDisplayModule>> _graphicLoader;
            std::unique_ptr<DLLoader<IGameModule>> _gameLoader;

            IDisplayModule* _graphic;
            IGameModule* _game;

            std::vector<std::string> _displayPath;
            std::vector<std::string> _gamePath;
            int _displayIdx;
            int _gameIdx;

            GameState _gameState;
            std::string _playerName;
            bool _isRunning;
    };
}

#endif /* !ARCADE_HPP */
