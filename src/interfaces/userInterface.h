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
 * @enum Player
 * @brief représente les joueurs
 */
typedef enum {
    CROIX,  //!< le joueur est une croix
    ROND,   //!< le joueur est un rond
    EMPTY   //!< la case est vide
} Player;

typedef struct {
    SDL_Rect rect;
    SDL_Color c;
} Boutton;

/**
 * @struct userInterface
 * @brief La structure userInterface contient les informations
 * nécessaires à l'affichage de l'interface graphique
 */
typedef struct ui {
    SDL_Window *window;      //!< La fenêtre SDL
    SDL_Renderer *renderer;  //!< Le renderer SDL
    Boutton *buttons;        //!< Les bouttons SDL
} userInterface;

#endif