/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_ncurses
*/


#include "ArcadeNcurses.hpp"
#include <ncurses.h>

static const std::string NCURSES_NAME = "nCurses";

arcade::ArcadeNcurses::ArcadeNcurses() : ADisplayModule(NCURSES_NAME) {}

void arcade::ArcadeNcurses::init()
{
    initscr();              // Démarre ncurses et crée la fenêtre principale (stdscr)
    cbreak();               // Rend les touches disponibles sans attendre Entrée
    noecho();               // Empêche l'affichage des touches tapées
    keypad(stdscr, TRUE);   // Active les touches spéciales (flèches, F1-F12…)
    curs_set(0);            // Cache le curseur
}

void arcade::ArcadeNcurses::stop()
{}

void arcade::ArcadeNcurses::clear() 
{}
