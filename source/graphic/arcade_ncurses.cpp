/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** arcade_ncurses
*/


#include "arcade_ncurses.hpp"
#include <ncurses.h>

arcade::arcade_ncurses::arcade_ncurses()
{
    _name = "nCurses";
}

void arcade::arcade_ncurses::init()
{
    initscr();              // Démarre ncurses et crée la fenêtre principale (stdscr)
    cbreak();               // Rend les touches disponibles sans attendre Entrée
    noecho();               // Empêche l'affichage des touches tapées
    keypad(stdscr, TRUE);   // Active les touches spéciales (flèches, F1-F12…)
    curs_set(0);            // Cache le curseur
}

void arcade::arcade_ncurses::stop()
{}

void arcade::arcade_ncurses::clear() 
{}
