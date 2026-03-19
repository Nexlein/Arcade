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

    class menu : public AGameModule {
        public:
        menu();
        ~menu();

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
        GameState _gameState;
    };
}

#endif /* !ARCADE_MENU_HPP */
