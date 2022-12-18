/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Fichier principale qui gère le back-end du jeu
 * @file: jouer.h
 */

#ifndef JOUER_H
#define JOUER_H

#include "../interfaces/sldInterface.h"
#include "../interfaces/textInterface.h"
#include "../interfaces/userInterface.h"

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/

/**
 * @brief Initialise le jeu
 * @param player Le joueur qui commence
 * @return Le jeu initialisé
 */
Puissance* puissance_init(Player player);

/**
 * @brief Joue le coup du joueur
 * @param game Le jeu
 * @param x La colonne
 * @param y La ligne
 * @return 0 si le coup est valide, 1 sinon
 */
void puissance_playGame(Puissance* game, userInterface ui);

/*
 ------------------------
 Fonction utils pour l'ia
 ------------------------
*/

/**
 * @brief Cherche la ligne où jouer le coup dans la colonne col
 * @param p Le tableau du jeu
 * @param col La colonne dans la quelle jouer
 * @return la ligne où jouer le coup
 */
int chercheLigne(Player p[][NB_COLONNES], int col);

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/

/**
 * @brief Met a jour le plateau de jeu sdl ou text avec un coup en [x,y]
 * @param game Le jeu
 * @param ui L'interface
 * @param x La colonne
 * @param y La ligne
 * @return 1 si le coup met fin a la partie, 0 sinon
 */
int joueCoup(Puissance* game, userInterface ui, int x, int y);

/**
 * @brief Traite les evenements du jeu en mode SDL
 * @param game le jeu
 * @param ui l'interface
 */
void playSDL(Puissance* game, userInterface ui);

/**
 * @brief Traite les evenements du jeu en mode texte
 * @param game le jeu
 * @param ui l'interface
 */
void playText(Puissance* game, userInterface ui);

#endif