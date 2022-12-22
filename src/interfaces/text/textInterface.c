/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente l'interface du jeu en vue texte
 * @file: textInterface.c
 */

#include "textInterface.h"

#include "../../rage.h"

/**
 * @brief: Initialise l'interface en vue texte
 * Les paramètres de l'interface sont initialisés à NULL
 * @return userInterface
 */
userInterface textInterface_init() {
    userInterface ui;
    ui.window = NULL, ui.renderer = NULL;
    return ui;
}

/**
 * @brief: Affiche le menu de choix du mode de jeu
 * IA vs IA, JOUEUR vs IA, JOUEUR vs JOUEUR
 * @return le choix de mode de jeu
 */
int choosePlayer() {
    int choice;
    printf("\033[H\033[2J");
    do {
        printf("Qui va s'affronter ?\n");
        printf("1. IA vs IA\n");
        printf("2. JOUEUR vs IA\n");
        printf("3. JOUEUR vs JOUEUR\n\n");
        printf("Choix: ");

        if (!scanf("%d", &choice)) {
            videBuffer();
            printf("\033[H\033[2J");
            printf("Choix invalide\n\n");
        } else if (choice < 1 || choice > 3) {
            printf("\033[H\033[2J");
            printf("Entrer une valeur entre 1 et 3\n\n");
        }
    } while (choice < 1 || choice > 3);
    return choice;
}

/**
 * @brief: Affiche le menu de choix de la difficulté de l'IA
 * facile, moyen, difficile
 * @return la difficulté de l'IA
 */
int dificulteIA() {
    int choice;
    printf("\033[H\033[2J");
    do {
        printf("Difficulté de l'IA ?\n");
        printf("1. Facile\n");
        printf("2. Moyen\n");
        printf("3. Difficile\n\n");
        printf("Choix: ");

        if (!scanf("%d", &choice)) {
            videBuffer();
            printf("\033[H\033[2J");
            printf("Choix invalide\n\n");
        } else if (choice < 1 || choice > 3) {
            printf("\033[H\033[2J");
            printf("Entrer une valeur entre 1 et 3\n\n");
        }
    } while (choice < 1 || choice > 3);
    return choice;
}

/**
 * @brief: Demmande à l'utilisateur s'il veut rejouer
 * @return le choix du joueur (1 oui ou 2 non)
 */
int rejouer() {
    int choice;
    printf("\033[H\033[2J");
    do {
        printf("Voulez-vous rejouer ?\n");
        printf("1. Oui\n");
        printf("2. Non\n\n");
        printf("Choix: ");

        if (!scanf("%d", &choice)) {
            videBuffer();
            printf("\033[H\033[2J");
            printf("Choix invalide\n\n");
        } else if (choice < 1 || choice > 2) {
            printf("\033[H\033[2J");
            printf("Entrer une valeur entre 1 et 2\n\n");
        }
    } while (choice < 1 || choice > 2);
    return choice;
}

/**
 * @brief Affiche la séparation entre 2 lignes du plateau de jeu
 */
void afficheLigneInter(int lig) {
    // On décolle l'affichage de la gauche
    printf("\n  ");
    // Si on est pas à la fin du plateau
    if (lig < NB_LIGNES - 1) {
        // On affiche la ligne de séparation
        for (int j = 0; j < NB_COLONNES - 1; j++) printf("---+");
        printf("---\n");
    } else {
        // Sinon on passe la ligne
        printf("\n");
    }
}

/**
 * @brief Affichage de l'index des colonnes
 */
void affichePremLigne() {
    printf("\n");
    // On affiche le nom des colonnes de 0 a NB_COLONNES
    for (int i = 0; i < NB_COLONNES; i++)
        (i == 0) ? printf("   %d ", i) : printf("  %d ", i);
    printf("\n");
}

/**
 * @brief Affiche le plateau de jeu
 * @param p le tableau de jeu de taille NB_LIGNES x NB_COLONNES
 */
void printBoard(Player p[][NB_COLONNES]) {
    int i, j;
    printf("\033[H\033[2J");
    //  Affichage de l'index des colonnes
    affichePremLigne();
    // Affichage du plateau
    for (i = 0; i < NB_LIGNES; i++) {
        // Affichage index colonnes
        printf("   ");
        for (j = 0; j < NB_COLONNES; j++) {
            // Affichage de la case en (i,j)
            (p[i][j] == EMPTY)
                ? printf(" ")
                : ((p[i][j] == ROND) ? printf("O") : printf("X"));
            // Affichage de la séparation entre les cases
            if (j < NB_COLONNES - 1) {
                printf(" | ");
            }
        }
        // Affichage de la séparation entre les lignes
        afficheLigneInter(i);
    }
}

/**
 * @brief vide le buffer de l'entrée standard
 */
void videBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}