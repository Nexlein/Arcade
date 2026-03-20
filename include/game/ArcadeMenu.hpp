/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

#ifndef ARCADE_MENU_HPP
#define ARCADE_MENU_HPP

#include "AGameModule.hpp"

namespace arcade {

    class ArcadeMenu : public AGameModule {
        public:
        ArcadeMenu(std::vector<std::string> _displayPath, std::vector<std::string> _gamePath);
        ~ArcadeMenu() = default;

        void restart() override;
        void handleInput(Key key) override;
        void update(float deltaTime) override;
        const std::vector<Entity>& getEntities() const override;
        const std::vector<Text>& getUIText() const override;
        RenderContext getRenderContext() const override;

        private:
        enum class CurrentChoice { ONGRAPHIC, ONGAME };
        void upKey();
        void downKey();
        void switchChoice(const Key& key);
        GameState _state;

        std::vector<std::string> _displayPath;
        std::vector<std::string> _gamePath;

        std::vector<Text> _uiText;
        CurrentChoice _currentIdx;
        int _displayIdx;
        int _gameIdx;
    };
}

#endif /* !ARCADE_MENU_HPP */
