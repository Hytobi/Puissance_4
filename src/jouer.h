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

Puissance* puissance_init(Player player);
void puissance_playGame(Puissance* game, userInterface ui);

// Pou l'ia
int chercheLigne(Player p[][NB_COLONNES], int col);

#endif