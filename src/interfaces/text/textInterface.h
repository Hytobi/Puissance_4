/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Gère l'interface du jeu en vue texte
 * @file: textInterface.h
 */

#ifndef TEXTINTERFACE_H
#define TEXTINTERFACE_H

#include "../userInterface.h"

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/
/**
 * @brief: Initialise l'interface en vue texte
 * Les paramètres de l'interface sont initialisés à NULL
 * @return userInterface
 */
userInterface textInterface_init();

/**
 * @brief: Affiche le menu de choix du mode de jeu
 * IA vs IA, JOUEUR vs IA, JOUEUR vs JOUEUR
 * @return le choix de mode de jeu
 */
int choosePlayer();

/**
 * @brief: Affiche le menu de choix de la dificulté de l'IA
 * facile, moyen, difficile
 * @return la difficulté de l'IA
 */
int dificulteIA();

/**
 * @brief Affiche le plateau de jeu
 * @param p le tableau de jeu de taille NB_LIGNES x NB_COLONNES
 */
void printBoard(Player p[][NB_COLONNES]);

/**
 * @brief vide le buffer de l'entrée standard
 */
void videBuffer();

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/
/**
 * @brief Affiche la séparation entre 2 lignes du plateau de jeu
 */
void afficheLigneInter(int lig);

/**
 * @brief Affichage de l'index des colonnes
 */
void affichePremLigne();

#endif