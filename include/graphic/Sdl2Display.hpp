/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SfmlDisplay
*/

#ifndef SFMLDISPLAY_HPP
#define SFMLDISPLAY_HPP

#include "ADisplayModule.hpp"
#include <map>

namespace arcade {
    class Sdl2Display : public ADisplayModule {
        public:
        Sdl2Display();
        ~Sdl2Display() = default;

        void init() override;
        void stop() override;
        void clear() override;

        void display() override;
        void drawEntity(const Entity& entity) override;
        void drawText(const Text& text) override;
        void drawRectangle(const Rect& rect, const Color& color) override;

        void pollEvents() override;
        Key getKey() override;
        MouseEvent getMouseEvent() override;
        int getWidth() const override;
        int getHeight() const override;

        bool isOpen() const override;

        void setTitle(const std::string& title) override;
        void setRenderContext(const RenderContext& context) override;

        private:
        TTF_Font *getFont(const std::string& path, int size);
        SDL_Texture *getSprite(const std::string& path);
        bool isValidFormat(const std::string& path);

        SDL_Window* _win;
        SDL_Renderer* _renderer;
        std::map<std::pair<std::string, int>, TTF_Font*> _fontCache;
        std::map<std::string, SDL_Texture*> _spriteCache;
    };
}  // namespace arcade

#endif /* !SFMLDISPLAY_HPP */
