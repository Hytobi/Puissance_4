/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère les événements de fin de partie
 * @file: jouer_fin.h
 */

#ifndef JOUER_FIN_H
#define JOUER_FIN_H

#include "jouer.h"
#include "userInterface.h"

// Fonction utils pour le main
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

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/

/**
 * @brief Vérifie si le plateau est plein
 *
 * @param p le tableau de jeu
 * @return 1 si le plateau est plein, 0 sinon
 */
int estPartiePleine(Player p[][NB_COLONNES]);

/**
 * @brief Vérifie si (l,c) est une case valide
 *
 * @param l la ligne de la case à tester
 * @param c la colonne de la case à tester
 * @return 1 si la case est valide, 0 sinon
 */
int estDansTab(int l, int c);

/**
 * @brief Compte l'alignement de pions dans une direction donnée
 *
 * @param p le plateau de jeu
 * @param val la valeur du pion à compter
 * @param lig la ligne du pion de départ
 * @param col la colonne du pion de départ
 * @param incL incrémentation de la ligne
 * @param incC incrémentation de la colonne
 * @return le nombre de pions alignés dans la direction donnée
 */
int compteValeur(Player p[][NB_COLONNES], Player val, int lig, int col,
                 int incL, int incC);

/**
 * @brief Maximum entre 4 entiers
 *
 * @param a un entier
 * @param b un entier
 * @param c un entier
 * @param d un entier
 * @return le plus grand des 4 entiers
 */
int max(int a, int b, int c, int d);

/**
 * @brief Vérifie si la partie est gagnée par un joueur
 *
 * @param p le plateau de jeu
 * @param val le joueur qui a potentiellement gagné
 * @param lig ligne de la dernière case jouée
 * @param col colonne de la dernière case jouée
 * @return le nombre de pions alignés au maximum
 */
int cGagne(Player p[][NB_COLONNES], Player val, int lig, int col);

#endif