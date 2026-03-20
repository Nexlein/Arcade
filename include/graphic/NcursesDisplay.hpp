/*
** EPITECH PROJECT, 2026
** G-OOP-400-MPL-4-1-arcade-5
** File description:
** NcursesDisplay
*/

#ifndef NCURSESDISPLAY_HPP
#define NCURSESDISPLAY_HPP

#include "ADisplayModule.hpp"

namespace arcade {
    class NcursesDisplay : public ADisplayModule {
        public:
        NcursesDisplay();
        ~NcursesDisplay() = default;

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

#endif /* !NCURSESDISPLAY_HPP */
