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
#include <chrono>

namespace arcade {
    class Arcade {
        public:
            Arcade(int ac, char* av[]);
            ~Arcade() = default;

            int run();
        private:
            /// @brief Prints the usage of the program
            /// @param programName The name of the program (typically argv[0])
            void printUsage(const std::string& programName) const;
            /// @brief Loads the libraries from the specified path
            /// @param loadPath The path from which to load the libraries (default is "./lib")
            void loadLibrairies(const std::string& loadPath = "lib");

            /// @brief Computes the elapsed time since the last frame
            /// @param lastTime The time of the last frame
            /// @return The elapsed time in seconds
            float computeElapsedTime(std::chrono::high_resolution_clock::time_point& lastTime) const;
            /// @brief Processes the inputs from the user
            /// @param key The key that was pressed
            /// @return True if the input was processed, false otherwise
            bool processInputs(arcade::Key& key);

            /// @brief Loads a game module from the specified path and starts it
            /// @param selectedGame The path of the selected game module
            void loadGameFromPath(const std::string& selectedGame);
            /// @brief Loads a display module from the specified path and switches to it
            /// @param selectedGraphic The path of the selected display module
            void loadDisplayFromPath(const std::string& selectedGraphic);

            /// @brief Handles the menu selection and transitions to the selected game or graphic library
            void handleMenuSelection();
            /// @brief Start the arcade menu
            void menuManager();
            /// @brief Handles state transitions based on the current game state and user input
            /// @param key The key that was pressed
            void handleStateTransitions(arcade::Key key);

            /// @brief Renders the current frame by drawing all entities and UI text
            void renderFrame();
            /// @brief Cleans up resources by stopping and deleting the game and display instances
            void cleanupResources();

            std::unique_ptr<DLLoader<IDisplayModule>> _graphicLoader;
            std::unique_ptr<DLLoader<IGameModule>> _gameLoader;

            IDisplayModule* _graphicInstance;
            IGameModule* _gameInstance;

            std::vector<std::string> _displayPaths;
            std::vector<std::string> _gamePaths;
            std::string _menuPath;

            int _displayIdx;
            int _gameIdx;

            GameState _gameState;
            std::string _playerName;
            bool _isRunning;
    };
}

#endif /* !ARCADE_HPP */
