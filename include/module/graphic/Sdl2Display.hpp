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
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

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
        float getDeltaTime() const override;
        int getWidth() const override;
        int getHeight() const override;
        bool isOpen() const override;

        void setTitle(const std::string& title) override;
        void setWindowSize(int width, int height) override;
        void setFullscreen(bool fullscreen) override;
        void setRenderContext(const RenderContext& context) override;

        private:
        TTF_Font *getFont(const std::string& path, int size);
        TTF_Font* tryOpenFont(const std::string& fontPath, int size);
        TTF_Font *getFallbackFont(int size);

        SDL_Texture *getSprite(const std::string& path);
        bool isValidFormat(const std::string& path);

        void stopFont();
        void stopSprite();

        SDL_Window* _win;
        SDL_Renderer* _renderer;
        std::queue<Key> _keyEvent;
        std::queue<MouseEvent> _mouseEvent;
        std::map<std::pair<std::string, int>, TTF_Font*> _fontCache;
        std::map<std::string, SDL_Texture*> _spriteCache;

        std::string _title;
        RenderContext _context;
        bool _fullscreen;
        float _currentTime;
        float _lastTime;
    };
}  // namespace arcade

#endif /* !SFMLDISPLAY_HPP */
