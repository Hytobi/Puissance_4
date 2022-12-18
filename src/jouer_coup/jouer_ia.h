/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Jouer le coup de l'ia
 * @file: jouer_ia.h
 */

#ifndef JOUER_IA_H
#define JOUER_IA_H

#include "../interfaces/userInterface.h"
#include "jouer.h"
#include "jouer_fin.h"

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/

/**
 * @brief Initialise le générateur de nombre aléatoire
 */
void initRandom();

/**
 * @brief Joue le coup de l'IA en fonction de son niveau
 * @param game le jeu
 * @return la colonne ou joue l'IA
 */
int chercheColonne(Puissance* game);

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/

/**
 * @brief Joue le coup de l'IA en mode facile
 * @param game
 * @return la colonne ou joue l'IA
 */
int facile(Puissance* game);

/**
 * @brief Test chaque colonne pour voir si le coup permet de gagner
 * @param game
 * @return la colonne ou peut gagner l'IA,-1 sinon
 */
int prochainCoupGagne(Player p[][NB_COLONNES], Player joueur);

/**
 * @brief pour l'IA moyen on joue le coup que l'adversaire devrait jouer
 * @param p le tableau de jeu
 * @param joueur le joueur courant (X ou O)
 * @return la colonne du coup a jouer
 */
int coupAdversaire(Player p[][NB_COLONNES], Player joueur);

/**
 * @brief Joue le coup de l'IA en mode moyen
 * @param game le jeu
 * @return la colonne ou joue l'IA
 */
int moyen(Puissance* game);

/**
 * @brief Joue le coup de l'IA en mode difficile
 * @param game le jeu
 * @return la colonne ou joue l'IA
 */
int difficile(Puissance* game);

#endif