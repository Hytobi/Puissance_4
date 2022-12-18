/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère l'interface du jeu en vue graphique SDL
 * @file: sdlInterface.h
 */

#ifndef SLDINTERFACE_H
#define SLDINTERFACE_H

#include "SDL2/SDL.h"
#include "userInterface.h"

#define CASE 140
#define H_WINDOW CASE* NB_LIGNES
#define W_WINDOW CASE*(NB_COLONNES + 1)

userInterface sdlInterface_init();
void updateBoard(userInterface ui, int x, int y, Player player);
void sdlInterface_start(userInterface ui);
void sdlInterface_printBoard(userInterface ui);

#endif