/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sdl2Display
*/

#include "Sdl2Display.hpp"
#include <iostream>
#include <filesystem>
#include <array>
#include <algorithm>
#include <unordered_map>

static const std::string DISPLAYNAME = "ArcadeMenu";
static const std::array<std::string_view, 3> VALID_FORMATS = {
    ".png", ".jpg", ".jpeg"
};

static const std::unordered_map<SDL_Keycode, arcade::Key> KEY_BINDINGS = {
    {SDLK_UP,        arcade::Key::NEXT_GAME},
    {SDLK_DOWN,      arcade::Key::PREV_GAME},
    {SDLK_LEFT,      arcade::Key::PREV_GRAPHICS},
    {SDLK_RIGHT,     arcade::Key::NEXT_GRAPHICS},
    {SDLK_SPACE,     arcade::Key::SPACE},
    {SDLK_RETURN,    arcade::Key::ENTER},
    {SDLK_ESCAPE,    arcade::Key::EXIT},
    {SDLK_BACKSPACE, arcade::Key::BACKSPACE},
    {SDLK_0,         arcade::Key::NUM_0},
    {SDLK_1,         arcade::Key::NUM_1},
    {SDLK_2,         arcade::Key::NUM_2},
    {SDLK_3,         arcade::Key::NUM_3},
    {SDLK_4,         arcade::Key::NUM_4},
    {SDLK_5,         arcade::Key::NUM_5},
    {SDLK_6,         arcade::Key::NUM_6},
    {SDLK_7,         arcade::Key::NUM_7},
    {SDLK_8,         arcade::Key::NUM_8},
    {SDLK_9,         arcade::Key::NUM_9},
    {SDLK_a,         arcade::Key::A},
    {SDLK_b,         arcade::Key::B},
    {SDLK_c,         arcade::Key::C},
    {SDLK_d,         arcade::Key::D},
    {SDLK_e,         arcade::Key::E},
    {SDLK_f,         arcade::Key::F},
    {SDLK_g,         arcade::Key::G},
    {SDLK_h,         arcade::Key::H},
    {SDLK_i,         arcade::Key::I},
    {SDLK_j,         arcade::Key::J},
    {SDLK_k,         arcade::Key::K},
    {SDLK_l,         arcade::Key::L},
    {SDLK_m,         arcade::Key::MENU},
    {SDLK_n,         arcade::Key::N},
    {SDLK_o,         arcade::Key::O},
    {SDLK_p,         arcade::Key::P},
    {SDLK_q,         arcade::Key::Q},
    {SDLK_r,         arcade::Key::RESTART},
    {SDLK_s,         arcade::Key::S},
    {SDLK_t,         arcade::Key::T},
    {SDLK_u,         arcade::Key::U},
    {SDLK_v,         arcade::Key::V},
    {SDLK_w,         arcade::Key::W},
    {SDLK_x,         arcade::Key::X},
    {SDLK_y,         arcade::Key::Y},
    {SDLK_z,         arcade::Key::Z},
};

static const std::unordered_map<SDL_Keycode, arcade::Key> MOUSE_BINDINGS = {
    {SDL_BUTTON_LEFT, arcade::Key::MOUSE_LEFT},
    {SDL_BUTTON_RIGHT, arcade::Key::MOUSE_RIGHT},
    {SDL_BUTTON_MIDDLE, arcade::Key::MOUSE_MIDDLE},
};

// gestion des size/fullscreen a revoir.

arcade::Sdl2Display::Sdl2Display()
    : ADisplayModule(DISPLAYNAME),
    _win(nullptr),
    _renderer(nullptr),
    _title(""),
    _context(1000, 1000, CoordinateSpace::GRID),
    _fullscreen(false),
    _currentTime(0.0),
    _lastTime(0.0) {}

void arcade::Sdl2Display::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
    if (TTF_Init() != 0) {
        SDL_Quit();
        throw std::runtime_error(std::string("TTF_Init failed: ") + TTF_GetError());
    }

    _win = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _context.width, _context.height, 0
    );
    if (!_win) {
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_DestroyWindow(_win);
        _win = nullptr;
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }
}

void arcade::Sdl2Display::clear()
{
    SDL_RenderClear(_renderer);
}

void arcade::Sdl2Display::display()
{
    SDL_RenderPresent(_renderer);
}

void arcade::Sdl2Display::pollEvents()
{
    SDL_Event event;

    _keyEvent = {};
    _mouseEvent = {};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            _win = nullptr;
        if (event.type == SDL_KEYDOWN) {
            auto it = KEY_BINDINGS.find(event.key.keysym.sym);
            _keyEvent.push(it != KEY_BINDINGS.end() ? it->second : Key::UNKNOWN);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            float x = static_cast<float>(event.button.x);
            float y = static_cast<float>(event.button.y);

            auto it = MOUSE_BINDINGS.find(event.button.button);
            _mouseEvent.push(
                it != MOUSE_BINDINGS.end() ?
                MouseEvent{{x, y}, it->second} :
                MouseEvent{Position{}, Key::UNKNOWN});
        }
    }
}

arcade::Key arcade::Sdl2Display::getKey()
{
    Key lastKey = _keyEvent.empty() ? Key::UNKNOWN : _keyEvent.front();

    _keyEvent.pop();
    return lastKey;
}

arcade::MouseEvent arcade::Sdl2Display::getMouseEvent()
{
    MouseEvent lastMouse = _mouseEvent.empty() ? MouseEvent{{0.0f, 0.0f}, Key::UNKNOWN} : _mouseEvent.front();

    _mouseEvent.pop();
    return lastMouse;
}

bool arcade::Sdl2Display::isValidFormat(const std::string& path)
{
    std::filesystem::path p(path);

    if (std::filesystem::exists(p) && std::filesystem::is_regular_file(p)) {
        std::string ext = p.extension().string();
        return std::find(VALID_FORMATS.begin(), VALID_FORMATS.end(), std::string_view(ext))
            != VALID_FORMATS.end();
    }
    return false;
}

SDL_Texture* arcade::Sdl2Display::getSprite(const std::string& path)
{
    auto it = _spriteCache.find(path);

    if (it != _spriteCache.end())
        return it->second;

    if (!isValidFormat(path))
        return nullptr;

    SDL_Texture *texture = IMG_LoadTexture(_renderer, "assets/sprite.png");
    if (!texture)
        throw std::runtime_error(IMG_GetError());
    _spriteCache[path] = texture;
    return texture;
}

void arcade::Sdl2Display::drawEntity(const Entity& entity)
{
    SDL_Texture *sprite = getSprite(entity.spritePath);

    // if (!sprite) throw
    SDL_Rect dst = {static_cast<int>(entity.pos.x), static_cast<int>(entity.pos.y), static_cast<int>(entity.size.x), static_cast<int>(entity.size.y)};
    SDL_RenderCopy(_renderer, sprite, nullptr, &dst);
}

TTF_Font* arcade::Sdl2Display::tryOpenFont(const std::string& fontPath, int size)
{
    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), size);
    return font;
}

const std::vector<std::string> FALLBACK_FONTS = {
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
};

TTF_Font *arcade::Sdl2Display::getFallbackFont(int size)
{
    for (const auto& fontPath : FALLBACK_FONTS) {
        TTF_Font *font = tryOpenFont(fontPath, size);
        if (font)
            return font;
    }

    std::cerr << "Warning: No fallback font found, attempting default SDL font" << std::endl;
    return nullptr;
}

TTF_Font *arcade::Sdl2Display::getFont(const std::string& path, int size)
{
    auto key = std::make_pair(path, size);
    auto it = _fontCache.find(key);

    if (it != _fontCache.end())
        return it->second;

    std::string fontPath = path.empty() ? "font/defaultFont.ttf" : path;
    TTF_Font *newFont = tryOpenFont(fontPath, size);

    // If the specified font is not found, try fallback fonts
    if (!newFont)
        newFont = getFallbackFont(size);

    if (!newFont)
        throw std::runtime_error("Failed to load font: " + fontPath + " and no fallback font available");

    _fontCache[key] = newFont;
    return newFont;
}

void arcade::Sdl2Display::drawText(const Text& text)
{
    TTF_Font *font = getFont(text.fontPath, text.fontSize);

    // if (!font) throw;
    SDL_Color color = {text.color.r, text.color.g, text.color.b, text.color.a};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.content.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dst = {static_cast<int>(text.pos.x), static_cast<int>(text.pos.y), 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
    // TODO: gestion anchor ici

    SDL_RenderCopy(_renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

void arcade::Sdl2Display::drawRectangle(const Rect& rect, const Color& color)
{
    SDL_Rect sdlRect = {static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.width), static_cast<int>(rect.height)};

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &sdlRect);
}

float arcade::Sdl2Display::getDeltaTime() const { return _currentTime - _lastTime; }

int arcade::Sdl2Display::getWidth() const { return _context.width; }

int arcade::Sdl2Display::getHeight() const { return _context.height; }

bool arcade::Sdl2Display::isOpen() const { return _win != nullptr; }

void arcade::Sdl2Display::setTitle(const std::string& title) { _title = title; }

void arcade::Sdl2Display::setWindowSize(int width, int height) { _context.width = width; _context.height = height; }

void arcade::Sdl2Display::setFullscreen(bool fullscreen) { _fullscreen = fullscreen; }

void arcade::Sdl2Display::setRenderContext(const RenderContext& context) { _context = context; }

void arcade::Sdl2Display::stopFont()
{
    for (auto& [key, font] : _fontCache)
        TTF_CloseFont(font);
    _fontCache.clear();
}

void arcade::Sdl2Display::stopSprite()
{
    for (auto& [path, texture] : _spriteCache)
        SDL_DestroyTexture(texture);
    _spriteCache.clear();
}

void arcade::Sdl2Display::stop()
{
    stopFont();
    stopSprite();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_win);
    TTF_Quit();
    SDL_Quit();
    _renderer = nullptr;
    _win = nullptr;
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::Sdl2Display();
    }
}
