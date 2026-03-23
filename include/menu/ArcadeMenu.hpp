/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_menu
*/

#ifndef ARCADE_MENU_HPP
#define ARCADE_MENU_HPP

#include "AGameModule.hpp"
#include "IMenuModule.hpp"

namespace arcade {

    class ArcadeMenu : public IMenuModule, public AGameModule {
        public:
        ArcadeMenu();
        ~ArcadeMenu() = default;

        void setDisplayPaths(const std::vector<std::string>& paths) override;
        void setGamePaths(const std::vector<std::string>& paths) override;

        void restart() override;
        void handleInput(Key key) override;
        void handleInput(MouseEvent mouseEvent) override;
        void update(float elapsedTime) override;
        const std::vector<Entity>& getEntities() const override;
        const std::vector<Text>& getUIText() const override;
        RenderContext getRenderContext() const override;

        const std::string& getSelectedGame() const override;
        const std::string& getSelectedGraphic() const override;

        private:
        enum class CurrentChoice { ONGRAPHIC, ONGAME };
        void upKey();
        void downKey();
        void switchChoice(const Key& key);

        std::vector<std::string> _displayPaths;
        std::vector<std::string> _gamePaths;

        std::vector<Entity> _entities;
        std::vector<Text> _uiText;
        CurrentChoice _currentSection;
        int _displayIdx;
        int _gameIdx;
    };
}

#endif /* !ARCADE_MENU_HPP */
