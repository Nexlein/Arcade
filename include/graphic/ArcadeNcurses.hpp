/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_ncurses
*/

#ifndef ARCADE_NCURSES_HPP
#define ARCADE_NCURSES_HPP

#include "ADisplayModule.hpp"

namespace arcade {
    class ArcadeNcurses : public ADisplayModule {
        public:
        ArcadeNcurses();
        ~ArcadeNcurses() = default;

        void init() override;
        void stop() override;
        void clear() override;
        void pollEvents() override;
        void display() override;
        void drawEntity(const Entity& entity) override;
        void drawText(const Text& text) override;
        void drawRectangle(const Rect& rect, const Color& color) override;
        Key getKey() override;
        MouseEvent getMouseEvent() override;
        bool isOpen() const override;
        void setTitle(const std::string& title) override;
        void setRenderContext(const RenderContext& context) override;
        int getWidth() const override;
        int getHeight() const override;
    };
}  // namespace arcade

#endif /* !ARCADE_NCURSES_HPP */
