/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_ncurses
*/


#include "NcursesDisplay.hpp"
#include <ncurses.h>

static const std::string NCURSES_NAME = "nCurses";

arcade::NcursesDisplay::NcursesDisplay() : ADisplayModule(NCURSES_NAME) {}

void arcade::NcursesDisplay::init()
{
    initscr();              // Démarre ncurses et crée la fenêtre principale (stdscr)
    cbreak();               // Rend les touches disponibles sans attendre Entrée
    noecho();               // Empêche l'affichage des touches tapées
    keypad(stdscr, TRUE);   // Active les touches spéciales (flèches, F1-F12…)
    curs_set(0);            // Cache le curseur
}

void arcade::NcursesDisplay::stop()
{}

void arcade::NcursesDisplay::pollEvents()
{}

void arcade::NcursesDisplay::clear() 
{}

arcade::MouseEvent arcade::NcursesDisplay::getMouseEvent()
{
    return MouseEvent();
}
