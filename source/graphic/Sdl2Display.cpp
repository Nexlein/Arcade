/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sdl2Display
*/

#include "Sdl2Display.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>

static const std::string DISPLAYNAME = "ArcadeMenu";

arcade::Sdl2Display::Sdl2Display()
    : ADisplayModule(DISPLAYNAME),
    _win(nullptr) {}

void arcade::Sdl2Display::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError()); // throw ?
    }
    TTF_Init();  // throw ?

    _win = SDL_CreateWindow(  // throw ?
        "GAME",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000, 1000, 0
    );
    _renderer = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
}

void arcade::Sdl2Display::stop()
{
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

// vérifier le format et apres si format est bon, alors on le charge dans le cache -> drawEntity;
bool arcade::Sdl2Display::isValidFormat(const std::string& path)
{
    
}

SDL_Texture* arcade::Sdl2Display::getSprite(const std::string& path)
{
    auto it = _spriteCache.find(path);

    if (it != _spriteCache.end())
        return it->second;
    
    if (!isValidFormat(path))
        return nullptr;
    SDL_Texture *texture = IMG_LoadTexture(_renderer, "assets/sprite.png");
    
}

void arcade::Sdl2Display::drawEntity(const Entity& entity)
{
    SDL_Texture *sprite = getSprite(entity.spritePath);

    // if (sprite == nullptr) throw
    // Dessin
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(_renderer, texture, nullptr, &dst);

    // Libération (dans le destructeur)
    SDL_DestroyTexture(texture);
}

TTF_Font *arcade::Sdl2Display::getFont(const std::string& path, int size)
{
    auto key = std::make_pair(path, size);
    auto it = _fontCache.find(key);

    if (it != _fontCache.end())
        return it->second;

    std::string fontPath = path.empty() ? "font/defaultFont.ttf" : path;
    TTF_Font *newFont = TTF_OpenFont(fontPath.c_str(), size);
    if (!newFont)
        std::cerr << "Error while loading new font" << std::endl;

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

    SDL_Rect dst = {(int)text.pos.x, (int)text.pos.y, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
    // TODO: gestion anchor ici

    SDL_RenderCopy(_renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

void arcade::Sdl2Display::drawRectangle(const Rect& rect, const Color& color)
{
    SDL_Rect sdlRect = {rect.x, rect.y, rect.width, rect.height};

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &sdlRect);
}

// extern "C" {
//     arcade::IModule* entryPoint() {
//         return new arcade::Sdl2Display();
//     }
// }
