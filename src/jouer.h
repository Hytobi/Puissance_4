/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Fichier principale qui gère le back-end du jeu
 * @file: jouer.h
 */

#ifndef JOUER_H
#define JOUER_H

#include "sldInterface.h"
#include "textInterface.h"
#include "userInterface.h"

typedef struct {
    Player board[NB_LIGNES][NB_COLONNES];
    Player player;
    int joueur;
    int ia;
} Puissance;

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/
Puissance* puissance_init(Player player);
void puissance_playGame(Puissance* game, userInterface ui);

/*
 ------------------------
 Fonction utils pour l'ia
 ------------------------
*/
int chercheLigne(Player p[][NB_COLONNES], int col);

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/
int joueCoup(Puissance* game, userInterface ui, int x, int y);
void playSDL(Puissance* game, userInterface ui);
void playText(Puissance* game, userInterface ui);

#endif