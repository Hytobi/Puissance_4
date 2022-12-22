/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 16/12/2022
 * @brief: Implémente les boutons de la SDL
 * @file: boutons.c
 */

#include "boutons.h"

#include <SDL2/SDL_image.h>

#include "../../rage.h"

/**
 * @brief Crée un bouton dans une interface SDL
 * @param ui l'interface
 * @param y coordonnée y du bouton
 * @param c La couleur du bouton
 * @return Bouton
 */
Bouton createButon(userInterface ui, int y, SDL_Color c) {
    return (Bouton){(SDL_Rect){X_BUTTON, y, W_BUTTON, H_BUTTON}, c};
}

/**
 * @brief Initialise les images sur les boutons
 * @param ui l'interface
 * @param i l'indice du bouton
 * @return SDL_Surface* l'image du bouton
 */
SDL_Surface* img_bouton(userInterface ui, int i) {
    SDL_Surface* image;
    switch (i) {
        case 0:
            image = IMG_Load("src/interfaces/sdl/img/Start.bmp");
            break;
        case 1:
            image = IMG_Load("src/interfaces/sdl/img/IAvsIA.bmp");
            break;
        case 2:
            image = IMG_Load("src/interfaces/sdl/img/J1vsIA.bmp");
            break;
        case 3:
            image = IMG_Load("src/interfaces/sdl/img/J1vsJ2.bmp");
            break;
        case 4:
            image = IMG_Load("src/interfaces/sdl/img/ia_facile.bmp");
            break;
        case 5:
            image = IMG_Load("src/interfaces/sdl/img/ia_moyen.bmp");
            break;
        case 6:
            image = IMG_Load("src/interfaces/sdl/img/ia_difficile.bmp");
            break;
        case 7:
            image = IMG_Load("src/interfaces/sdl/img/Regles.bmp");
            break;
        default:
            RAGE_QUIT(ui, "Probleme assignation des butons");
            break;
    }
    if (!image) RAGE_QUIT(ui, "IMG_Load img_bouton");
    return image;
}

/**
 * @brief Affiche le bouton sur l'interface
 * @param ui l'interface
 * @param i l'indice du bouton
 */
void affiche_btn(userInterface ui, int i) {
    Bouton btn = ui.buttons[i];
    SDL_Rect size_img;

    // Si c'est un boutton de sélection de mode ou de difficulté
    if (i != 0 && i != 7) {
        // On recupere la taille de l'image
        size_img = (SDL_Rect){X_BUTTON, btn.rect.y, W_IMG, H_IMG};
        // On set la couleur de fond du bouton
        SDL_SetRenderDrawColor(ui.renderer, btn.c.r, btn.c.g, btn.c.b, btn.c.a);
        // On dessine l'arrière du bouton
        SDL_Rect back = (SDL_Rect){X_BUTTON + 3, btn.rect.y + 3, W_IMG, H_IMG};
        SDL_RenderFillRect(ui.renderer, &back);
    } else {
        // Sinon on affiche le bouton entier
        size_img = btn.rect;
    }
    // On charge l'image
    SDL_Surface* image = img_bouton(ui, i);
    if (!image) RAGE_QUIT(ui, "IMG_Load affiche_btn");
    // On crée la texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ui.renderer, image);
    if (!texture) {
        SDL_FreeSurface(image);
        RAGE_QUIT(ui, "SDL_CreateTextureFromSurface affiche btn");
    }
    // On affiche l'image
    SDL_RenderCopy(ui.renderer, texture, NULL, &size_img);
    SDL_RenderPresent(ui.renderer);
    // On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

/**
 * @brief Test si la souris est dans le bouton i
 * @param ui l'interface
 * @param x coordonnée x de la souris
 * @param y coordonnée y de la souris
 * @param i l'indice du bouton à tester
 * @return 1 si la souris est dans le bouton, 0 sinon
 */
int test_estDansBtn(userInterface ui, int x, int y, int i) {
    return x >= X_BUTTON && x < X_BUTTON + W_BUTTON &&
           y >= ui.buttons[i].rect.y && y < ui.buttons[i].rect.y + H_BUTTON;
}

/**
 * @brief Set la couleur arrière du bouton i
 * @param ui l'inteface
 * @param i l'indice du bouton à modifier
 * @param c La nouvelle couleur
 */
void setColor(userInterface ui, int i, SDL_Color c) {
    ui.buttons[i].c = c;
    affiche_btn(ui, i);
}

/**
 * @brief Set la couleur arrière de tous les boutons à la couleur par défaut
 * @param ui l'interface
 */
void resetColor(userInterface ui) {
    for (int i = 0; i < NB_BTN; i++) {
        ui.buttons[i].c = COLOR_BACK_NOT_CLICK;
    }
}

/**
 * @brief Initialise les boutons de l'interface
 * @param ui l'interface
 */
void initButons(userInterface ui) {
    // On crée les boutons Start et Regles au même endroit
    ui.buttons[0] = createButon(ui, H_WINDOW - 80, COLOR_BACK_IS_CLICK);
    ui.buttons[7] = createButon(ui, H_WINDOW - 80, COLOR_BACK_IS_CLICK);
    // On crée les boutons de sélection de mode et de difficulté
    for (int i = 1; i < NB_BTN / 2; i++) {
        ui.buttons[i] =
            createButon(ui, Y_MODE + (i - 1) * ESPACE, COLOR_BACK_NOT_CLICK);
        ui.buttons[i + 3] = createButon(ui, Y_DIFFICULTE + (i - 1) * ESPACE,
                                        COLOR_BACK_NOT_CLICK);
    }
}
