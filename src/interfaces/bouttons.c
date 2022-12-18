/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 16/12/2022
 * @brief: Implémente les bouttons de la SDL
 * @file: sdlInterface.c
 */

#include "bouttons.h"

// a voir plus tard pour ecrire dans le boutton
// #include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../rage.h"

Boutton createButton(userInterface ui, int y, SDL_Color c) {
    return (Boutton){(SDL_Rect){X_BUTTON, y, W_BUTTON, H_BUTTON}, c};
}

SDL_Surface* img_boutton(userInterface ui, int i) {
    SDL_Surface* image;
    switch (i) {
        case 0:
            image = IMG_Load("src/interfaces/img/Suivant.bmp");
            break;
        case 1:
            image = IMG_Load("src/interfaces/img/IAvsIA.bmp");
            break;
        case 2:
            image = IMG_Load("src/interfaces/img/J1vsIA.bmp");
            break;
        case 3:
            image = IMG_Load("src/interfaces/img/J1vsJ2.bmp");
            break;
        case 4:
            image = IMG_Load("src/interfaces/img/ia_facile.bmp");
            break;
        case 5:
            image = IMG_Load("src/interfaces/img/ia_moyen.bmp");
            break;
        case 6:
            image = IMG_Load("src/interfaces/img/ia_dificile.bmp");
            break;
        case 7:
            image = IMG_Load("src/interfaces/img/Suivant.bmp");
            break;
        default:
            printf("%d\n", i);
            RAGE_QUIT(ui, "Probleme assignation des buttons");
            break;
    }

    if (NULL == image) {
        fprintf(stderr, "Erreur IMG_Load : %s\n", SDL_GetError());
    }
    return image;
}

void affiche_btn(userInterface ui, int i) {
    Boutton btn = ui.buttons[i];
    SDL_Rect size_img;
    if (i != 0 && i != 7) {
        size_img = (SDL_Rect){X_BUTTON, btn.rect.y, W_IMG, H_IMG};
        SDL_SetRenderDrawColor(ui.renderer, btn.c.r, btn.c.g, btn.c.b, btn.c.a);
        SDL_Rect back = (SDL_Rect){X_BUTTON + 3, btn.rect.y + 3, W_IMG, H_IMG};
        SDL_RenderFillRect(ui.renderer, &back);
    } else {
        size_img = btn.rect;
    }

    SDL_Surface* image = img_boutton(ui, i);

    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(ui.renderer, image);
    SDL_FreeSurface(image);
    if (NULL == texture2) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n",
                SDL_GetError());
    }

    SDL_RenderCopy(ui.renderer, texture2, NULL, &size_img);
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
            createButton(ui, X_MODE + (i - 1) * ESPACE, COLOR_BACK_NOT_CLICK);
        ui.buttons[i + 3] = createButton(ui, X_DIFFICULTE + (i - 1) * ESPACE,
                                         COLOR_BACK_NOT_CLICK);
    }
}