/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IMenuModule
*/

#ifndef IMENU_MODULE_HPP
#define IMENU_MODULE_HPP

#include <string>
#include <vector>

namespace arcade {
    class IMenuModule {
        public:
            virtual ~IMenuModule() = default;

            /// @brief Sets the paths of the available display libraries
            /// @param paths The paths of the available display libraries
            virtual void setDisplayPaths(const std::vector<std::string>& paths) = 0;
            /// @brief Sets the paths of the available game libraries
            /// @param paths The paths of the available game libraries
            virtual void setGamePaths(const std::vector<std::string>& paths) = 0;

            /// @brief Set the index of the currently loaded graphic library.
            /// @param idx index of the display library currently loaded.
            virtual void setDisplayIdx(const int idx) = 0;

            /// @brief Gets the path of the selected game library
            /// @return The path of the selected game library
            virtual const std::string& getSelectedGame() const = 0;
            /// @brief Gets the path of the selected graphic library
            /// @return The path of the selected graphic library
            virtual const std::string& getSelectedGraphic() const = 0;
    };
}

#endif /* !IMENU_MODULE_HPP */
