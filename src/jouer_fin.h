/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère les événements de fin de partie
 * @file: jouer_fin.h
 */

#ifndef JOUER_FIN_H
#define JOUER_FIN_H

#include "jouer.h"
#include "userInterface.h"

/**
 * @brief Vérifie si on peut placer un jeton dans la colonne col
 *
 * @param p le tableau de jeu
 * @param col la colonne a tester
 * @return  1 si la colonne est valide, 0 sinon
 */
int estColonneValide(Player p[][NB_COLONNES], int col);

/**
 * @brief Vérifie si quelqu'un a gagné ou si le plateau est plein
 *
 * @param game Les données du jeu Puissance 4
 * @param ui L'interface utilisateur pour savoir comment finir le programme
 * @param x La ligne du dernier coup joué
 * @param y La colonne du dernier coup joué
 * @return 1 si la partie est finie, 0 sinon
 */
int verifFinPartie(Puissance* game, userInterface ui, int x, int y);

#endif