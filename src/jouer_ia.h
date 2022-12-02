/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Jouer le coup de l'ia
 * @file: jouer_ia.h
 */

#ifndef JOUER_IA_H
#define JOUER_IA_H

#include "jouer.h"
#include "jouer_fin.h"
#include "userInterface.h"

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/
void initRandom();
int chercheColonne(Puissance* game);
int cGagne(Player p[][NB_COLONNES], Player val, int lig, int col);

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/

int prochainCoupGagne(Player p[][NB_COLONNES], Player joueur);

int coupAdversaire(Player p[][NB_COLONNES], Player joueur);

#endif