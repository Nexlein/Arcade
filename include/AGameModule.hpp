/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** AGameModule
*/

/// @file AGameModule.hpp
/// @brief Abstract base class for game modules

#pragma once

#include "IGameModule.hpp"

namespace arcade {

    /// @class AGameModule
    /// @brief Abstract implementation of IGameModule that provides getType()
    ///
    /// This class implements the getType() method returning ModuleType::GAME.
    /// All concrete game modules (Snake, Pacman, etc.) should inherit from
    /// this class instead of IGameModule directly.
    class AGameModule : public IGameModule {
        public:
        /// @brief Virtual destructor
        AGameModule(std::string name = "Unnamed Game") : _name(name) {}
        virtual ~AGameModule() = default;

        /// @brief Get the type of this module
        /// @return ModuleType::GAME
        ModuleType getType() const override { return ModuleType::GAME; }
        const std::string& getName() const override { return _name; }

        protected:
        std::string _name;
    };
}  // namespace arcade
