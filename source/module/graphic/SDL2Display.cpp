/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** SDL2Display
*/

/// @file SDL2Display.cpp
/// @brief Implementation of the SDL2Display class, which provides an SDL2-based display module for
/// the Arcade project.

#include "SDL2Display.hpp"
#include "ADisplayModule.hpp"

#include <algorithm>
#include <array>
#include <filesystem>
#include <unordered_map>

/// @brief Name of the SDL2 display module
static const std::string DISPLAY_NAME = "ArcadeMenu";

/// @brief Valid image formats for sprites
static const std::array<std::string_view, 3> VALID_FORMATS = {".png", ".jpg", ".jpeg"};

/// @brief Mapping of SDL key codes to arcade::Key values
static const std::unordered_map<SDL_Keycode, arcade::Key> KEY_BINDINGS = {
    {SDLK_UP, arcade::Key::UP},
    {SDLK_DOWN, arcade::Key::DOWN},
    {SDLK_LEFT, arcade::Key::LEFT},
    {SDLK_RIGHT, arcade::Key::RIGHT},
    {SDLK_SPACE, arcade::Key::SPACE},
    {SDLK_RETURN, arcade::Key::ENTER},
    {SDLK_ESCAPE, arcade::Key::EXIT},
    {SDLK_BACKSPACE, arcade::Key::BACKSPACE},
    {SDLK_0, arcade::Key::NUM_0},
    {SDLK_1, arcade::Key::PREV_GAME},
    {SDLK_2, arcade::Key::NEXT_GAME},
    {SDLK_3, arcade::Key::PREV_GRAPHICS},
    {SDLK_4, arcade::Key::NEXT_GRAPHICS},
    {SDLK_5, arcade::Key::NUM_5},
    {SDLK_6, arcade::Key::NUM_6},
    {SDLK_7, arcade::Key::NUM_7},
    {SDLK_8, arcade::Key::NUM_8},
    {SDLK_9, arcade::Key::NUM_9},
    {SDLK_a, arcade::Key::A},
    {SDLK_b, arcade::Key::B},
    {SDLK_c, arcade::Key::C},
    {SDLK_d, arcade::Key::D},
    {SDLK_e, arcade::Key::E},
    {SDLK_f, arcade::Key::F},
    {SDLK_g, arcade::Key::G},
    {SDLK_h, arcade::Key::H},
    {SDLK_i, arcade::Key::I},
    {SDLK_j, arcade::Key::J},
    {SDLK_k, arcade::Key::K},
    {SDLK_l, arcade::Key::L},
    {SDLK_m, arcade::Key::MENU},
    {SDLK_n, arcade::Key::N},
    {SDLK_o, arcade::Key::O},
    {SDLK_p, arcade::Key::P},
    {SDLK_q, arcade::Key::Q},
    {SDLK_r, arcade::Key::RESTART},
    {SDLK_s, arcade::Key::S},
    {SDLK_t, arcade::Key::T},
    {SDLK_u, arcade::Key::U},
    {SDLK_v, arcade::Key::V},
    {SDLK_w, arcade::Key::W},
    {SDLK_x, arcade::Key::X},
    {SDLK_y, arcade::Key::Y},
    {SDLK_z, arcade::Key::Z}
};

/// @brief Mapping of SDL mouse button codes to arcade::Key values
static const std::unordered_map<SDL_Keycode, arcade::Key> MOUSE_BINDINGS = {
    {SDL_BUTTON_LEFT, arcade::Key::MOUSE_LEFT},
    {SDL_BUTTON_RIGHT, arcade::Key::MOUSE_RIGHT},
    {SDL_BUTTON_MIDDLE, arcade::Key::MOUSE_MIDDLE},
};

// TODO: gestion des size/fullscreen a revoir.
arcade::SDL2Display::SDL2Display() : ADisplayModule(DISPLAY_NAME), _win(nullptr), _renderer(nullptr)
{}

arcade::SDL2Display::~SDL2Display() { stop(); }

void arcade::SDL2Display::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) throw std::runtime_error(SDL_GetError());
    if (TTF_Init() != 0) {
        SDL_Quit();
        throw std::runtime_error(TTF_GetError());
    }

    _win = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            _context.width, _context.height, SDL_WINDOW_RESIZABLE);
    if (!_win) {
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_DestroyWindow(_win);
        _win = nullptr;
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }
}

void arcade::SDL2Display::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void arcade::SDL2Display::stopFont()
{
    for (auto& [key, font] : _fontCache) TTF_CloseFont(font);
    _fontCache.clear();
}

void arcade::SDL2Display::stopSprite()
{
    for (auto& [path, texture] : _spriteCache) SDL_DestroyTexture(texture);
    _spriteCache.clear();
}

void arcade::SDL2Display::stop()
{
    stopFont();
    stopSprite();

    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_win) {
        SDL_DestroyWindow(_win);
        _win = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool arcade::SDL2Display::isOpen() const { return _win != nullptr; }

void arcade::SDL2Display::pollEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) _win = nullptr;
        if (event.type == SDL_KEYDOWN) {
            auto it = KEY_BINDINGS.find(event.key.keysym.sym);
            if (it != KEY_BINDINGS.end()) _keyEvent.push(it->second);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            float x = static_cast<float>(event.button.x);
            float y = static_cast<float>(event.button.y);

            auto it = MOUSE_BINDINGS.find(event.button.button);
            if (it != MOUSE_BINDINGS.end()) _mouseEvent.push(MouseEvent{{x, y}, it->second});
            else _mouseEvent.push(MouseEvent{Position{}, Key::UNKNOWN});
        }
    }
}

bool arcade::SDL2Display::isValidFormat(const std::string& path)
{
    std::filesystem::path p(path);

    if (std::filesystem::exists(p) && std::filesystem::is_regular_file(p)) {
        std::string ext = p.extension().string();
        return std::find(VALID_FORMATS.begin(), VALID_FORMATS.end(), std::string_view(ext)) !=
               VALID_FORMATS.end();
    }
    return false;
}

SDL_Texture* arcade::SDL2Display::getSprite(const std::string& path)
{
    auto it = _spriteCache.find(path);

    if (it != _spriteCache.end()) return it->second;

    if (!isValidFormat(path)) return nullptr;

    SDL_Texture* texture = IMG_LoadTexture(_renderer, path.c_str());
    if (!texture)
        return nullptr;
    _spriteCache[path] = texture;
    return texture;
}

arcade::ADisplayModule::Viewport arcade::SDL2Display::computeViewport() const
{
    int winW, winH;
    SDL_GetWindowSize(_win, &winW, &winH);

    float scaleX = static_cast<float>(winW) / _context.width;
    float scaleY = static_cast<float>(winH) / _context.height;
    float scale  = std::min(scaleX, scaleY);

    int offsetX = static_cast<int>((winW - _context.width  * scale) / 2.0f);
    int offsetY = static_cast<int>((winH - _context.height * scale) / 2.0f);

    return {scale, offsetX, offsetY};
}

void arcade::SDL2Display::applyScaling(SDL_Rect& dst)
{
    auto [scale, offsetX, offsetY] = computeViewport();

    float x0 = dst.x * scale;
    float y0 = dst.y * scale;
    float x1 = (dst.x + dst.w) * scale;
    float y1 = (dst.y + dst.h) * scale;

    dst.x = static_cast<int>(std::floor(x0)) + offsetX;
    dst.y = static_cast<int>(std::floor(y0)) + offsetY;
    dst.w = static_cast<int>(std::ceil(x1)) - static_cast<int>(std::floor(x0));
    dst.h = static_cast<int>(std::ceil(y1)) - static_cast<int>(std::floor(y0));
}

void arcade::SDL2Display::drawEntity(const Entity& entity)
{
    SDL_Rect dst = {static_cast<int>(entity.pos.x), static_cast<int>(entity.pos.y),
                static_cast<int>(entity.size.x), static_cast<int>(entity.size.y)};

    applyScaling(dst);
    applyAnchor(entity.anchor, dst);

    SDL_Texture* sprite = nullptr;
    if (!entity.spritePath.empty())
        sprite = getSprite(entity.spritePath);

    if (sprite) {
        SDL_RenderCopy(_renderer, sprite, nullptr, &dst);
    } else {
        SDL_SetRenderDrawColor(_renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
        SDL_RenderFillRect(_renderer, &dst);
    }
}

TTF_Font* arcade::SDL2Display::tryOpenFont(const std::string& fontPath, int size)
{
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
    return font;
}

TTF_Font* arcade::SDL2Display::getFallbackFont(int size)
{
    // List of common fallback font paths to try
    std::vector<std::string> fallbackFonts = {
        "font/defaultFont.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/Library/Fonts/Arial.ttf",
        "C:\\Windows\\Fonts\\Arial.ttf"
    };

    for (const auto& path : fallbackFonts) {
        TTF_Font* font = tryOpenFont(path, size);
        if (font) return font;
    }
    return nullptr;
}

TTF_Font* arcade::SDL2Display::getFont(const std::string& path, int size)
{
    auto key = std::make_pair(path, size);

    // Check if the font is already loaded in the cache
    auto it = _fontCache.find(key);
    if (it != _fontCache.end()) return it->second;

    TTF_Font* font = tryOpenFont(path, size);

    // If the specified font is not found, try fallback fonts
    if (!font) font = getFallbackFont(size);

    if (!font)
        throw std::runtime_error("Failed to load font: " + path);

    _fontCache[key] = font;
    return font;
}

void arcade::SDL2Display::drawText(const Text& text)
{
    TTF_Font* font = getFont(text.fontPath, text.fontSize);

    SDL_Color color = {text.color.r, text.color.g, text.color.b, text.color.a};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.content.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dst = {static_cast<int>(text.pos.x), static_cast<int>(text.pos.y), 0, 0};
    applyScaling(dst);
    SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
    applyAnchor(text.anchor, dst);

    SDL_RenderCopy(_renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

void arcade::SDL2Display::drawRectangle(const Rect& rect, const Color& color)
{
    SDL_Rect sdlRect = {static_cast<int>(rect.x), static_cast<int>(rect.y),
                        static_cast<int>(rect.width), static_cast<int>(rect.height)};

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &sdlRect);
}

void arcade::SDL2Display::applyAnchor(Anchor anchor, SDL_Rect& dst)
{
    switch (anchor) {
    case Anchor::TOP_LEFT: break;
    case Anchor::TOP_CENTER:    dst.x -= dst.w / 2; break;
    case Anchor::TOP_RIGHT:     dst.x -= dst.w; break;
    case Anchor::MIDDLE_LEFT:   dst.y -= dst.h / 2; break;
    case Anchor::CENTER:        dst.x -= dst.w / 2; dst.y -= dst.h / 2; break;
    case Anchor::MIDDLE_RIGHT:  dst.x -= dst.w; dst.y -= dst.h / 2; break;
    case Anchor::BOTTOM_LEFT:   dst.y -= dst.h; break;
    case Anchor::BOTTOM_CENTER: dst.x -= dst.w / 2; dst.y -= dst.h; break;
    case Anchor::BOTTOM_RIGHT:  dst.x -= dst.w; dst.y -= dst.h; break;
    }
}

void arcade::SDL2Display::display() { SDL_RenderPresent(_renderer); }

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::SDL2Display();
    }
}
