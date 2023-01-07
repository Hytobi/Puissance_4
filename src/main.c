/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Fonction principale du programme
 * @file: src/main.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "interfaces/sdl/sldInterface.h"
#include "interfaces/text/textInterface.h"
#include "interfaces/userInterface.h"
#include "jouer_coup/jouer.h"

/**
 * @brief Première affichage du programme, demande à l'utilisateur de choisir
 * entre l'interface graphique ou textuelle
 *
 * @return Le type d'interface choisi
 */
int chooseInterface() {
    int choice;
    printf("\033[H\033[2J");
    printf("[main] Puissance 4\n\n");
    do {
        printf("Choix de l'interface:\n");
        printf("1. Text\n");
        printf("2. SDL\n");
        printf("3. Quitter\n\n");
        printf("Choix : ");

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
 * @brief Fonction principale du programme
 *
 * @return 0
 */
int main(int arvc, char** argv) {
    // Récupération du chemin vers les images
    char* path;
    // Si le programme n'est pas lancé depuis le dossier Puissance_4
    if (strcmp(argv[0], "./bin/exec")) {
        path = (char*)malloc((strlen(argv[0]) - 8) * sizeof(char));
        // On récupère le chemin vers le dossier Puissance_4
        strncpy(path, argv[0], strlen(argv[0]) - 8);
    } else {
        // Sinon on met le chemin à NULL
        path = NULL;
    }

    // Choix de l'interface via le terminal de commande
    int choice = chooseInterface();
    if (choice == 3) return EXIT_SUCCESS;

    // Initialisation des paramètres de jeu
    Puissance* game = puissance_init(CROIX);

    // Initialisation de l'interface
    userInterface ui;
    if (choice == 1)
        ui = textInterface_init();
    else if (choice == 2) {
        ui = sdlInterface_init(path);
        // Si l'utilisateur quitte sans avoir fait start 1 fois
        if (!ui.window) goto quit;
    }

    // Lancement du jeu
    puissance_playGame(game, ui);

// Libération de la mémoire
quit:
    free(game);
    if (path != NULL) free(path);
    return EXIT_SUCCESS;
}  // main