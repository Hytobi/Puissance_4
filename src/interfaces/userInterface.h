/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère l'interface utilisateur
 * @file: src/interfaces/userInterface.h
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

/**
 * @struct Bouton
 * @brief La structure Bouton contient les informations
 * nécessaires à l'affichage d'un bouton
 */
typedef struct {
    SDL_Rect rect;  //!< La position et la taille du bouton
    SDL_Color c;    //!< La couleur du bouton
} Bouton;

/**
 * @struct userInterface
 * @brief La structure userInterface contient les informations
 * nécessaires à l'affichage de l'interface graphique
 */
typedef struct ui {
    SDL_Window *window;      //!< La fenêtre SDL
    SDL_Renderer *renderer;  //!< Le renderer SDL
    Bouton *buttons;         //!< Les boutons SDL
    char *path;              //!< Le chemin vers les images
} userInterface;

/**
 * @struct Puissance
 * @brief Structure qui représente le jeu
 */
typedef struct {
    Player board[NB_LIGNES][NB_COLONNES];  //!< Le plateau de jeu
    Player player;                         //!< Le joueur courant
    int joueur;                            //!< Le mode de jeu
    int ia;                                //!< Difficulté de l'ia
} Puissance;

#endif