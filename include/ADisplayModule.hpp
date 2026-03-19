/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** ADisplayModule
*/

/// @file ADisplayModule.hpp
/// @brief Abstract base class for display modules

#pragma once

#include "IDisplayModule.hpp"

namespace arcade {

    /// @class ADisplayModule
    /// @brief Abstract implementation of IDisplayModule that provides getType()
    ///
    /// This class implements the getType() method returning ModuleType::DISPLAY.
    /// All concrete display modules (SDL2, SFML, nCurses, etc.) should inherit from
    /// this class instead of IDisplayModule directly.
    class ADisplayModule : public IDisplayModule {
        public:
        /// @brief Virtual destructor
        virtual ~ADisplayModule() = default;

        /// @brief Get the type of this module
        /// @return ModuleType::DISPLAY
        ModuleType getType() const override { return ModuleType::DISPLAY; }
        const std::string& getName() const override { return _name; }

        protected:
        std::string _name;
    };
}  // namespace arcade
