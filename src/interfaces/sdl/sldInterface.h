/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère l'interface du jeu en vue graphique SDL
 * @file: sdlInterface.h
 */

#ifndef SLDINTERFACE_H
#define SLDINTERFACE_H

#include "../userInterface.h"
#include "SDL2/SDL.h"

// Taille de la fenetre en pixel
#define CASE 140
#define H_WINDOW CASE* NB_LIGNES
#define W_WINDOW CASE*(NB_COLONNES + 1)

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/

/**
 * @brief Initialise l'inteface utilisateur ui pour la sdl
 * Les parametres de l'interface ne doivent pas etre null à la fin
 * @return l'interface utilisateur
 */
userInterface sdlInterface_init();

/**
 * @brief Met a jour le plateau de jeu en mettant le pion de la couleur du
 * joueur en position (x,y)
 * @param ui l'interface
 * @param x la position en x
 * @param y la position en y
 * @param player le joueur (X ou O)
 */
void updateBoard(userInterface ui, int x, int y, Player player);

/**
 * @brief Page de demarrage de la vue SDL
 * @param ui l'interface
 * @return 0 si tout s'est bien passé, 1 si l'utilisateur a fermé la fenetre
 */
int sdlInterface_start(userInterface ui);

/**
 * @brief Affiche le gagnant de la partie ou un match nul
 * @param ui l'interface
 * @param fin entier qui indique le gagnant 1 pour rouge 2 pour jaune 0 pour nul
 */
void sdlInterface_end(userInterface ui, int fin);

/**
 * @brief Attend que le mode de jeu et la difficulté de l'ia soit choisi pour la
 * sdl
 * @param game Le jeu
 * @param ui L'interface
 * @return 1 si on quitte, 0 sinon
 */
int choixModeEtIa(Puissance* game, userInterface ui);

/**
 * @brief Fait une pause de 2 secondes pour laisser le temps de voir le coup de
 * l'ia Il y a un bug dans SDL_WaitEventTimeout qui ne retourn pas 0 si le temps
 * est écoulé On garde cette solution pour pouvoir quitter le jeu quand l'ia
 * joue Contrairment à la solution avec SDL_Delay qui ne permet pas de quitter
 * le jeu
 * @return int 1 si l'utilisateur a quitté, 0 sinon
 */
int pauseSDL();

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/

/**
 * @brief Initialise l'interface en vue graphique SDL
 * On met la fenetre en blanc
 * @param ui l'interface
 */
void resetBack(userInterface ui);

/**
 * @brief Affiche les règles du jeu pour la sdl
 * @param ui l'interface
 */
void load_regles(userInterface ui);

/**
 * @brief Affiche le plateau de jeu dans la vue SDL
 * Ainsi que les boutons pour les modes de jeu
 * @param ui l'interface
 */
void sdlInterface_printBoard(userInterface ui);

#endif