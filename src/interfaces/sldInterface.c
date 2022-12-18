/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente l'interface du jeu en vue graphique SDL
 * @file: sdlInterface.c
 */

#include "sldInterface.h"

#include "bouttons.h"

// a voir plus tard pour ecrire dans le boutton
// #include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../rage.h"

void resetBack(userInterface ui) {
    SDL_SetRenderDrawColor(ui.renderer, 255, 255, 255, 255);
    SDL_RenderClear(ui.renderer);
    SDL_SetRenderDrawColor(ui.renderer, 0, 0, 0, 255);
}

void sdlInterface_start(userInterface ui) {
    resetBack(ui);
    affiche_btn(ui, 0);
    int x, y;
    SDL_Event event;
    // Tant que pas suivant on attend
    while (SDL_WaitEvent(&event) > 0) {
        if (event.type == SDL_QUIT) break;
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&x, &y);
            if (test_estDansBtn(ui, x, y, 0)) {
                break;
            }
        }
    }
}
void sdlInterface_end(userInterface ui, char c) {
    SDL_Rect rect = (SDL_Rect){2 * CASE + CASE / 2, CASE / 2, 2 * CASE, CASE};
    // On print un rectangle avec un message du gagnant

    SDL_SetRenderDrawColor(ui.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(ui.renderer, &rect);
    SDL_RenderPresent(ui.renderer);
}

void sdlInterface_printBoard(userInterface ui) {
    resetBack(ui);
    for (int i = 1; i <= NB_BTN; i++) affiche_btn(ui, i);
    for (int i = 1; i <= NB_COLONNES; i++)
        SDL_RenderDrawLine(ui.renderer, CASE * i, 0, CASE * i, H_WINDOW);
    for (int i = 1; i < NB_LIGNES; i++)
        SDL_RenderDrawLine(ui.renderer, 0, CASE * i, W_WINDOW - CASE, i * CASE);
    SDL_RenderPresent(ui.renderer);
}

userInterface sdlInterface_init() {
    userInterface ui;
    ui.window = NULL, ui.renderer = NULL;
    ui.buttons = malloc(sizeof(Boutton) * NB_BTN);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        RAGE_QUIT(ui, "SDL_Init");
    }
    ui.window = SDL_CreateWindow("Puissance 4", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, W_WINDOW, H_WINDOW,
                                 SDL_WINDOW_SHOWN);
    if (ui.window == NULL) {
        RAGE_QUIT(ui, "SDL_CreateWindow");
    }
    ui.renderer = SDL_CreateRenderer(ui.window, -1, 0);
    if (ui.renderer == NULL) {
        RAGE_QUIT(ui, "SDL_CreateRenderer");
    }
    // Fond blanc
    resetBack(ui);
    SDL_RenderPresent(ui.renderer);
    initButtons(ui);

    // On affiche la page de start
    sdlInterface_start(ui);

    return ui;
}

void updateBoard(userInterface ui, int x, int y, Player player) {
    if (player == CROIX) {
        SDL_SetRenderDrawColor(ui.renderer, 255, 0, 0, 255);
    } else if (player == ROND) {
        SDL_SetRenderDrawColor(ui.renderer, 255, 255, 0, 255);
    }
    x *= CASE;
    y *= CASE;
    int radus = CASE * 30;
    int midX = x + CASE / 2;
    int midY = y + CASE / 2;

    for (int i = y + 1; i < y + CASE - 1; i++) {
        for (int j = x + 1; j < x + CASE - 1; j++) {
            if ((midY - i) * (midY - i) + (midX - j) * (midX - j) < radus) {
                SDL_RenderDrawLine(ui.renderer, midY, midX, i, j);
            }
        }
    }
    SDL_RenderPresent(ui.renderer);
}
