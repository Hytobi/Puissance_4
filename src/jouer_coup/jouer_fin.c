/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente les événements de fin de partie
 * @file: jouer_fin.h
 */
#include "jouer_fin.h"

#include <unistd.h>

#include "SDL2/SDL.h"

/**
 * @brief Vérifie si on peut placer un jeton dans la colonne col
 *
 * @param p le tableau de jeu
 * @param col la colonne a tester
 * @return  1 si la colonne est valide, 0 sinon
 */
int estColonneValide(Player p[][NB_COLONNES], int col) {
    return (col >= 0 && col < NB_COLONNES && p[0][col] == EMPTY);
}

/**
 * @brief Vérifie si le plateau est plein
 *
 * @param p le tableau de jeu
 * @return 1 si le plateau est plein, 0 sinon
 */
int estPartiePleine(Player p[][NB_COLONNES]) {
    // O regard juste la premier ligne comme on empile les jetons
    for (int c = 0; c < NB_COLONNES; c++)
        // Si on trouve une case vide, la partie n'est pas pleine
        if (p[0][c] == EMPTY) return 0;

    return 1;
}

/**
 * @brief Vérifie si (l,c) est une case valide
 *
 * @param l la ligne de la case à tester
 * @param c la colonne de la case à tester
 * @return 1 si la case est valide, 0 sinon
 */
int estDansTab(int l, int c) {
    return (l >= 0 && l < NB_LIGNES && c >= 0 && c < NB_COLONNES);
}

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
                 int incL, int incC) {
    if (incL == 0 && incC == 0) return 1;
    // On commence a 1 car p[lig][col] est déjà égal à val
    int total = 1, l, c;
    // On incrémente la ligne et la colonne
    l = lig + incL;
    c = col + incC;
    // Tant qu'on est dans le tableau on continue
    while (estDansTab(l, c)) {
        // Si val n'est pas dans p[l][c], on arrête
        if (p[l][c] != val) return total;
        // Sinon on incrémente le total
        total++;
        // On incrémente la ligne et la colonne
        l += incL;
        c += incC;
    }
    return total;
}

/**
 * @brief Maximum entre 4 entiers
 *
 * @param a un entier
 * @param b un entier
 * @param c un entier
 * @param d un entier
 * @return le plus grand des 4 entiers
 */
int max(int a, int b, int c, int d) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}

/**
 * @brief Vérifie si la partie est gagnée par un joueur
 *
 * @param p le plateau de jeu
 * @param val le joueur qui a potentiellement gagné
 * @param lig ligne de la dernière case jouée
 * @param col colonne de la dernière case jouée
 * @return le nombre de pions alignés au maximum
 */
int cGagne(Player p[][NB_COLONNES], Player val, int lig, int col) {
    int h, v, dd, dg;
    // Horizontal
    h = compteValeur(p, val, lig, col, 0, 1) +
        compteValeur(p, val, lig, col, 0, -1) - 1;
    // Vertical
    v = compteValeur(p, val, lig, col, 1, 0);
    // Diagonale droite
    dd = compteValeur(p, val, lig, col, 1, 1) +
         compteValeur(p, val, lig, col, -1, -1) - 1;
    // Diagonale gauche
    dg = compteValeur(p, val, lig, col, 1, -1) +
         compteValeur(p, val, lig, col, -1, 1) - 1;
    return max(h, v, dd, dg);
}

/**
 * @brief Vérifie si quelqu'un a gagné ou si le plateau est plein
 *
 * @param game Les données du jeu Puissance 4
 * @param ui L'interface utilisateur pour savoir comment finir le programme
 * @param x La ligne du dernier coup joué
 * @param y La colonne du dernier coup joué
 * @return 1 si la partie est finie, 0 sinon
 */
int verifFinPartie(Puissance* game, userInterface ui, int x, int y) {
    // Si le joueur a aligné au moins 4 pions, il a gagné
    if (cGagne(game->board, game->player, x, y) >= 4) {
        // Si on n'est pas dans la sdl on est dans le terminal
        if (ui.renderer) {
            sdlInterface_end(ui, game->player == CROIX ? 1 : 2);
            SDL_Delay(5000);
        } else {
            printf("%s a gagné\n", game->player == CROIX ? "X" : "O");
            sleep(5);
        }
        return 1;
    }
    // Si la partie est pleine
    if (estPartiePleine(game->board)) {
        if (ui.renderer) {
            sdlInterface_end(ui, 0);
            SDL_Delay(5000);
        } else {
            printf("Partie Nul !\n");
            sleep(5);
        }
        return 1;
    }
    // Sinon on change de joueur
    game->player = game->player == CROIX ? ROND : CROIX;
    return 0;
}
// Fin vérifie si le joueur a gagné