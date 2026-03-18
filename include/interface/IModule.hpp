/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IModule
*/

/// @file IModule.hpp
/// @brief Base interface for all Arcade modules (games and display libraries)

#pragma once

#include <string>

namespace arcade {

    /// @enum ModuleType
    /// @brief Identifies the type of module
    enum class ModuleType {
        DISPLAY,  ///< Graphics/display library module
        GAME      ///< Game logic module
    };

    /// @class IModule
    /// @brief Base interface for all Arcade modules
    ///
    /// This interface provides common functionality for both game and display modules.
    /// All modules must implement getType() to identify themselves at runtime.
    class IModule {
        public:
        /// @brief Virtual destructor
        virtual ~IModule() = default;

        /// @brief Get the type of this module
        /// @return Whether this is a DISPLAY or GAME module
        virtual ModuleType getType() const = 0;

        /// @brief Get the name of this module
        /// @return Human-readable name (e.g., "SDL2", "Snake", "nCurses")
        virtual const std::string& getName() const = 0;
    };
}  // namespace arcade
