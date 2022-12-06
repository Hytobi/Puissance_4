/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente le coup de l'ia
 * @file: jouer_ia.c
 */

#include "jouer_ia.h"

#include <time.h>

void initRandom() { srand(time(NULL)); }

int facile(Puissance* game) {
    int c;
    do {
        c = rand() % NB_COLONNES;
    } while (!estColonneValide(game->board, c));
    return c;
}

int prochainCoupGagne(Player p[][NB_COLONNES], Player joueur) {
    int l, c;
    for (c = 0; c < NB_COLONNES; c++) {
        if (p[0][c] != EMPTY) continue;
        l = chercheLigne(p, c);
        if (p[l][c] == EMPTY) {
            p[l][c] = joueur;
            if (cGagne(p, joueur, l, c) >= 4) {
                p[l][c] = EMPTY;
                return c;
            }
            p[l][c] = EMPTY;
        }
    }
    return -1;
}

int coupAdversaire(Player p[][NB_COLONNES], Player joueur) {
    int l, c, t, js, max = 0, size = 0;
    int tab[NB_COLONNES] = {-1};

    // Comme je joue le coup de l'adversaire le pb est la
    Player joueurSuivant = (joueur == ROND) ? CROIX : ROND;

    // On teste tous les coups possibles
    for (c = 0; c < NB_COLONNES; c++) {
        // Si la colonne est pleine on passe au coup suivant
        if (p[0][c] != EMPTY) continue;

        // On cherche la ligne pour se placer
        l = chercheLigne(p, c);

        // On joue le coup de l'adversaire
        p[l][c] = joueurSuivant;

        // Si il aligne plus de pions que precedemment
        if ((t = cGagne(p, joueurSuivant, l, c)) >= max) {
            // js est le nombre de pions alignés par l'adversaire au coup
            // suivant si je joue el (l,c)

            // Cette partie du code :
            // https://www.instagram.com/reel/Ckkq2nCJNq5/?igshid=YmMyMTA2M2Y=
            // p[l - 1][c] = joueur;
            js = cGagne(p, joueur, l - 1, c);
            // printf("js = %d et c=%d\n", js, c);
            //  p[l - 1][c] = EMPTY;

            // Si il trouve un meilleur coup que le précédent
            // On remet le tableau à 0
            if (t > max && js < 3) {
                size = 0;
                tab[size++] = c;
                max = t;
                // printf("\nNouveau tab et j'ajoute %d ", c);
            } else {
                // On ajoute le coup dans le tableau si le prochain joueur ne
                // peut pas aligné 3 pions grace a nous
                if (js < 3) {
                    // printf("%d ", c);
                    tab[size++] = c;
                }
            }
        }
        p[l][c] = EMPTY;
    }
    // Si on a trop de coup a jouer on joue au centre
    if (size >= 6) {
        // colonne dans {2,3,4}
        return (rand() % 3) + 2;
    }
    if (size) return tab[rand() % size];
    return -1;
}

int moyen(Puissance* game) {
    int c;
    // Si on peut gagner on gagne
    c = prochainCoupGagne(game->board, game->player);
    if (c != -1) return c;

    // Si l'adversaire peut gagner on bloque
    c = prochainCoupGagne(game->board, (game->player == ROND) ? CROIX : ROND);
    if (c != -1) return c;

    // Sinon on joue le coup de l'adversaire
    do {
        c = coupAdversaire(game->board, game->player);
        // Si vraiment ca se passe mal on joue au hasard
        if (c == -1) {
            printf("au hasard");
            c = rand() % NB_COLONNES;
        }
    } while (!estColonneValide(game->board, c));

    return c;
}

int difficile(Puissance* game) { return 3; }

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