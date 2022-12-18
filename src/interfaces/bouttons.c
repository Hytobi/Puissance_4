/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 16/12/2022
 * @brief: Implémente les bouttons de la SDL
 * @file: sdlInterface.c
 */

#include "bouttons.h"

// a voir plus tard pour ecrire dans le boutton
#include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>

#include "../rage.h"

Boutton createButton(userInterface ui, int y, SDL_Color c) {
    return (Boutton){(SDL_Rect){X_BUTTON, y, W_BUTTON, H_BUTTON}, c};
}

char* nom_boutton(userInterface ui, int i) {
    char* mot = malloc(sizeof(char) * 8);
    switch (i) {
        case 0:
            mot = "Jouer";
            break;
        case 1:
            mot = "IA vs IA";
            break;
        case 2:
            mot = "J1 vs IA";
            break;
        case 3:
            mot = "J1 vs 1";
            break;
        case 4:
            mot = "Facile";
            break;
        case 5:
            mot = "Moyen";
            break;
        case 6:
            mot = "Dificile";
            break;
        case 7:
            mot = "Regle";
            break;
        default:
            RAGE_QUIT(ui, "Probleme assignation des buttons");
            break;
    }
    return mot;
}

void affiche_btn(userInterface ui, int i) {
    Boutton btn = ui.buttons[i];

    /*
    char* nom = nom_boutton(ui,i);

    ici on met le message que va comporter le btn
    peut etre faire une fonction qui retourn un char*
    comportant une case qui selon i donne le msg

    */

    SDL_SetRenderDrawColor(ui.renderer, btn.c.r, btn.c.g, btn.c.b, btn.c.a);
    SDL_RenderFillRect(ui.renderer, &btn.rect);
    SDL_RenderPresent(ui.renderer);
}

int test_estDansBtn(userInterface ui, int x, int y, int i) {
    return x >= X_BUTTON && x < X_BUTTON + W_BUTTON &&
           y >= ui.buttons[i].rect.y && y < ui.buttons[i].rect.y + H_BUTTON;
}

void setColor(userInterface ui, int i, SDL_Color c) {
    ui.buttons[i].c = c;
    affiche_btn(ui, i);
}

void initButtons(userInterface ui) {
    ui.buttons[0] = createButton(ui, H_WINDOW - 80, COLOR_BTN_UTIL);
    ui.buttons[7] = createButton(ui, H_WINDOW - 80, COLOR_BTN_UTIL);
    for (int i = 1; i < NB_BTN / 2; i++) {
        ui.buttons[i] =
            createButton(ui, X_MODE + (i - 1) * ESPACE, COLOR_BTN_JOUEUR);
        ui.buttons[i + 3] =
            createButton(ui, X_DIFFICULTE + (i - 1) * ESPACE, COLOR_BTN_IA);
    }
}