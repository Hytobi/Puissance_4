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
int main() {
    // Choix de l'interface via le terminal de commande
    int choice = chooseInterface();
    if (choice == 3) return EXIT_SUCCESS;

    // Initialisation des paramètres de jeu
    Puissance *game = puissance_init(CROIX);

    // Initialisation de l'interface
    userInterface ui;
    if (choice == 1)
        ui = textInterface_init();
    else if (choice == 2) {
        ui = sdlInterface_init();
        // Si l'utilisateur quitte sans avoir fait start 1 fois
        if (!ui.window) return EXIT_SUCCESS;
    }

    // Lancement du jeu
    puissance_playGame(game, ui);

    free(game);

    return EXIT_SUCCESS;
}  // main