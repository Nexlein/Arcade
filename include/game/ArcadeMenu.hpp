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
        ArcadeMenu();
        ~ArcadeMenu() = default;

        void setDisplayPaths(const std::vector<std::string>& paths);
        void setGamePaths(const std::vector<std::string>& paths);

        void restart() override;
        void handleInput(Key key) override;
        void handleInput(MouseEvent mouseEvent) override;
        void update(float elapsedTime) override;
        const std::vector<Entity>& getEntities() const override;
        const std::vector<Text>& getUIText() const override;
        RenderContext getRenderContext() const override;

        const std::string& getSelectedGame() const;
        const std::string& getSelectedGraphic() const;

        private:
        enum class CurrentChoice { ONGRAPHIC, ONGAME };
        void upKey();
        void downKey();
        void switchChoice(const Key& key);

        std::vector<std::string> _displayPath;
        std::vector<std::string> _gamePath;

        std::vector<Entity> _entities;
        std::vector<Text> _uiText;
        CurrentChoice _currentSection;
        int _displayIdx;
        int _gameIdx;
    };
}

#endif /* !ARCADE_MENU_HPP */
