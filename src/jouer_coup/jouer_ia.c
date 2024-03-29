/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente le coup de l'ia
 * @file: src/jouer_coup/jouer_ia.c
 */

#include "jouer_ia.h"

#include <time.h>

/**
 * @brief Initialise le générateur de nombre aléatoire
 */
void initRandom() { srand(time(NULL)); }

/**
 * @brief Test chaque colonne pour voir si le coup permet de gagner
 * @param game
 * @return la colonne ou peut gagner l'IA,-1 sinon
 */
int prochainCoupGagne(Player p[][NB_COLONNES], Player joueur) {
    int l, c;
    // On parcours les colonnes
    for (c = 0; c < NB_COLONNES; c++) {
        // Si la colonne est pleine on passe au coup suivant
        if (p[0][c] != EMPTY) continue;
        // On cherche la ligne pour placer le pion
        l = chercheLigne(p, c);
        // Si la case est bien vide;
        if (p[l][c] == EMPTY) {
            // On joue le coup
            p[l][c] = joueur;
            // Puis on regard si ce coup permet d'aligner 4 pions ou plus
            if (cGagne(p, joueur, l, c) >= 4) {
                // Si oui on remet la case à vide et on retourne la colonne
                p[l][c] = EMPTY;
                return c;
            }
            // Sinon on remet la case à vide
            p[l][c] = EMPTY;
        }
    }
    // Si aucun coup ne permet de gagner on retourne -1
    return -1;
}

/**
 * @brief Joue un coup gagnant a 100% si possible,
 * ou bloque le coup cagant de l'adversaire
 *
 * @param game le jeu
 * @return int la colonne ou jouer
 */
int blockOuGagne(Puissance* game) {
    int c;
    // Si on peut gagner on gagne
    c = prochainCoupGagne(game->board, game->player);
    if (c != -1) return c;

    // Si l'adversaire peut gagner on bloque
    c = prochainCoupGagne(game->board, (game->player == ROND) ? CROIX : ROND);
    if (c != -1) return c;
    // Sinon on retourne -1
    return -1;
}

/**
 * @brief Joue le coup de l'IA en mode facile
 * @param game
 * @return la colonne ou joue l'IA
 */
int facile(Puissance* game) {
    int c;
    // On cherche une colonne valide
    do {
        c = rand() % NB_COLONNES;
    } while (!estColonneValide(game->board, c));
    return c;
}

/**
 * @brief pour l'IA moyen on joue le coup que l'adversaire devrait jouer
 * @param p le tableau de jeu
 * @param joueur le joueur courant (X ou O)
 * @return la colonne du coup a jouer
 */
int coupAdversaire(Player p[][NB_COLONNES], Player joueur) {
    // Petite video explicative :
    // https://www.instagram.com/reel/Ckkq2nCJNq5/?igshid=YmMyMTA2M2Y=

    int l, c, t, js, max = 0, size = 0;
    int tab[NB_COLONNES] = {-1};

    // On recupere le joueur suivant
    Player joueurSuivant = (joueur == ROND) ? CROIX : ROND;

    // On teste tous les coups possibles
    for (c = 0; c < NB_COLONNES; c++) {
        // Si la colonne est pleine on passe au coup suivant
        if (p[0][c] != EMPTY) continue;

        // On cherche la ligne pour se placer
        l = chercheLigne(p, c);

        // On joue le coup de l'adversaire
        p[l][c] = joueurSuivant;
        if (l != 0) p[l - 1][c] = joueurSuivant;

        // Si il aligne plus de pions que precedemment
        if ((t = cGagne(p, joueurSuivant, l, c)) >= max) {
            // nombre de pions alignés par l'adversaire au coup apres le notre
            if (l != 0) js = cGagne(p, joueurSuivant, l - 1, c);

            // Si il trouve un meilleur coup que le précédent
            // On remet le tableau à 0
            if (t > max && js < 4) {
                size = 0;
                tab[size++] = c;
                max = t;
            } else {
                // On ajoute le coup dans le tableau si le prochain joueur ne
                // peut pas aligné 3 pions grace a nous
                if (js < 3) {
                    tab[size++] = c;
                }
            }
        }
        // On remet la case à vide
        p[l][c] = EMPTY;
        if (l != 0) p[l - 1][c] = EMPTY;
    }
    // Si on a trop de coup a jouer on joue au centre
    if (size >= 6) {
        // Une colonne dans {2,3,4}
        return (rand() % 3) + 2;
    }
    // Sinon on joue dans une colonne que le tableau contient
    if (size) return tab[rand() % size];
    // Si on a rien trouvé on retourne -1
    return -1;
}

/**
 * @brief Joue le coup de l'IA en mode moyen
 * @param game le jeu
 * @return la colonne ou joue l'IA
 */
int moyen(Puissance* game) {
    int c;
    // On regarde si on peut gagner ou bloquer
    c = blockOuGagne(game);
    if (c != -1) return c;

    // Sinon on joue le coup de l'adversaire
    do {
        c = coupAdversaire(game->board, game->player);
        // Si vraiment ca se passe mal on joue au hasard
        if (c == -1) {
            c = rand() % NB_COLONNES;
        }
    } while (!estColonneValide(game->board, c));

    return c;
}

/**
 * @brief Joue le coup de l'IA en mode difficile
 * @param game le jeu
 * @return la colonne ou joue l'IA
 */
int difficile(Puissance* game) {
    int c;
    // On regarde si on peut gagner ou bloquer
    c = blockOuGagne(game);
    if (c != -1) return c;

    int col[3] = {-1};
    int lig[2] = {-1};
    Player p;

    // On regard 2 coup dans le futur
    for (int i = 0; i < 2; i++) {
        if (i % 2 == 0)
            p = game->player;
        else
            p = (game->player == ROND) ? CROIX : ROND;
        // On joue le coup de l'adversaire
        col[i] = coupAdversaire(game->board, p);
        // Si vraiment ca se passe mal on joue au hasard
        if (col[i] == -1) {
            col[i] = rand() % NB_COLONNES;
        }
        lig[i] = chercheLigne(game->board, col[i]);
        game->board[lig[i]][col[i]] = p;
    }

    // On joue le 3eme coup dans le futur
    col[2] = coupAdversaire(game->board, game->player);

    // On remet le jeu a l'etat initial
    for (int i = 0; i < 2; i++) {
        game->board[lig[i]][col[i]] = EMPTY;
    }
    // Si on a pas de coup a jouer on joue au hasard
    if (col[2] == -1) {
        return facile(game);
    }
    // Sinon on joue le coup
    return col[2];
}

/**
 * @brief Joue le coup de l'IA en fonction de son niveau
 * @param game le jeu
 * @return la colonne ou joue l'IA
 */
int chercheColonne(Puissance* game) {
    initRandom();
    if (game->ia == 1) {
        return facile(game);
    } else if (game->ia == 2) {
        return moyen(game);
    } else {
        return difficile(game);
    }
}