/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère l'interface utilisateur
 * @file: userInterface.h
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "SDL2/SDL.h"
#define NB_COLONNES 7
#define NB_LIGNES 6

/**
 * @brief Le joueur est soit un rond soit une croix
 * Si la case est vide, le joueur est EMPTY
 */
typedef enum { CROIX, ROND, EMPTY } Player;

/**
 * @brief La structure userInterface contient les informations
 * nécessaires à l'affichage de l'interface graphique
 * @param window La fenêtre SDL
 * @param renderer Le renderer SDL
 */
typedef struct ui {
    SDL_Window *window;
    SDL_Renderer *renderer;

} userInterface;

#endif