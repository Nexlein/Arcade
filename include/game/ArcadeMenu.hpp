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
        ~ArcadeMenu();

        void init() override;
        void stop() override;
        void update(float deltaTime) override;
        void handleInput(Key key) override;
        const std::vector<Entity>& getEntities() const override;
        const std::vector<Text>& getUIText() const override;
        GameState getState() const override;
        int getScore() const override;
        void restart() override;
        void pause() override;
        void resume() override;
        RenderContext getRenderContext() const override;

        private:
        GameState _state;

        std::vector<std::string> _displayPath;
        std::vector<std::string> _gamePath;
        int _displayIdx;
        int _gameIdx;
    };
}

#endif /* !ARCADE_MENU_HPP */
