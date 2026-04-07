/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** LIBCACADisplay
*/

#include "ALLEGRO5Display.hpp"

static const std::string DISPLAY_NAME = "Allegro5";

arcade::ALLEGRO5::ALLEGRO5() : ADisplayModule(DISPLAY_NAME) {}

arcade::ALLEGRO5::~ALLEGRO5() { stop(); }

void arcade::ALLEGRO5::init()
{
    if (!al_init()) throw std::runtime_error("Failed to initialize Allegro");

    al_install_keyboard();
    al_init_image_addon();

    _win = al_create_display(_context.width, _context.height);
    if (!_win) throw std::runtime_error("Failed to create Allegro display");

    al_set_window_title(_win, "Arcade");
}

extern "C" {
    arcade::IModule* entryPoint() {
        return new arcade::ALLEGRO5();
    }
}