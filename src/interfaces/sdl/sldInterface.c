/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente l'interface du jeu en vue graphique SDL
 * @file: sdlInterface.c
 */

#include "sldInterface.h"

#include <SDL2/SDL_image.h>

#include "../../rage.h"
#include "boutons.h"

/**
 * @brief Initialise l'interface en vue graphique SDL
 * On met la fenetre en blanc
 * @param ui l'interface
 */
void resetBack(userInterface ui) {
    SDL_SetRenderDrawColor(ui.renderer, 255, 255, 255, 255);
    SDL_RenderClear(ui.renderer);
    SDL_SetRenderDrawColor(ui.renderer, 0, 0, 0, 255);
}

/**
 * @brief Affiche les règles du jeu pour la sdl
 * @param ui l'interface
 */
void load_regles(userInterface ui) {
    // Les règles du jeu sont dans une image qu'on charge
    SDL_Surface *image = IMG_Load("src/interfaces/sdl/img/Puissance4.bmp");
    if (NULL == image) {
        RAGE_QUIT(ui, "IMG_Load regle");
    }

    // On crée une texture à partir de l'image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ui.renderer, image);
    if (NULL == texture) {
        SDL_FreeSurface(image);
        RAGE_QUIT(ui, "SDL_CreateTextureFromSurface regle");
    }

    // On affiche la texture sur la fenetre
    SDL_Rect rect = (SDL_Rect){0, 0, W_WINDOW, H_WINDOW - CASE};
    SDL_RenderCopy(ui.renderer, texture, NULL, &rect);
    SDL_RenderPresent(ui.renderer);

    // On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

/**
 * @brief Page de demarrage de la vue SDL
 * @param ui l'interface
 */
void sdlInterface_start(userInterface ui) {
    // Au cas ou on relis les règles on remet le fond blanc
    resetBack(ui);
    // On charge les règles
    load_regles(ui);
    // On affiche le bouton Start
    affiche_btn(ui, 0);
    // On attend que l'utilisateur clique sur le bouton
    int x, y;
    SDL_Event event;
    while (SDL_WaitEvent(&event) > 0) {
        // On quitte si l'utilisateur ferme la fenetre
        if (event.type == SDL_QUIT) break;
        // Si l'utilisateur clique
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // On récupère les coordonnées de la souris
            SDL_GetMouseState(&x, &y);
            // On regarde si l'utilisateur a cliqué sur le bouton
            if (test_estDansBtn(ui, x, y, 0)) {
                break;
            }
        }
    }
}

/**
 * @brief Affiche le gagnant de la partie ou un match nul
 * @param ui l'interface
 * @param fin entier qui indique le gagnant 1 pour rouge 2 pour jaune 0 pour nul
 */
void sdlInterface_end(userInterface ui, int fin) {
    // On print un rectangle avec un message du gagnant
    SDL_Surface *image;
    if (fin == 1)
        image = IMG_Load("src/interfaces/sdl/img/Rouge.bmp");
    else if (fin == 2)
        image = IMG_Load("src/interfaces/sdl/img/Jaune.bmp");
    else
        image = IMG_Load("src/interfaces/sdl/img/MatchNul.bmp");

    // On quitte si on a pas pu charger l'image
    if (!image) {
        RAGE_QUIT(ui, "IMG_Load end");
    }
    // On crée une texture à partir de l'image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ui.renderer, image);
    if (!texture) {
        SDL_FreeSurface(image);
        RAGE_QUIT(ui, "SDL_CreateTextureFromSurface end");
    }

    // On affiche la texture sur la fenetre
    SDL_Rect rect = (SDL_Rect){2 * CASE + CASE / 2, CASE / 2, 2 * CASE, CASE};
    SDL_RenderCopy(ui.renderer, texture, NULL, &rect);
    SDL_RenderPresent(ui.renderer);

    // On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

/**
 * @brief Affiche le plateau de jeu dans la vue SDL
 * Ainsi que les boutons pour les modes de jeu
 * @param ui l'interface
 */
void sdlInterface_printBoard(userInterface ui) {
    // On remet le fond blanc pour tout supprimer
    resetBack(ui);
    // On affiche les boutons
    for (int i = 1; i < NB_BTN; i++) affiche_btn(ui, i);
    // On affiche le plateau en noir
    SDL_SetRenderDrawColor(ui.renderer, 0, 0, 0, 255);
    for (int i = 1; i <= NB_COLONNES; i++)
        SDL_RenderDrawLine(ui.renderer, CASE * i, 0, CASE * i, H_WINDOW);
    for (int i = 1; i < NB_LIGNES; i++)
        SDL_RenderDrawLine(ui.renderer, 0, CASE * i, W_WINDOW - CASE, i * CASE);
    SDL_RenderPresent(ui.renderer);
}

/**
 * @brief Initialise l'inteface utilisateur ui pour la sdl
 * Les parametres de l'interface ne doivent pas etre null à la fin
 * @return l'interface utilisateur
 */
userInterface sdlInterface_init() {
    // Initialisation de l'interface
    userInterface ui;
    ui.window = NULL, ui.renderer = NULL;
    ui.buttons = malloc(sizeof(Bouton) * NB_BTN);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) RAGE_QUIT(ui, "SDL_Init");

    // On crée la fenetre
    ui.window = SDL_CreateWindow("Puissance 4", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, W_WINDOW, H_WINDOW,
                                 SDL_WINDOW_SHOWN);
    if (ui.window == NULL) RAGE_QUIT(ui, "SDL_CreateWindow");

    // On crée le renderer
    ui.renderer = SDL_CreateRenderer(ui.window, -1, 0);
    if (ui.renderer == NULL) RAGE_QUIT(ui, "SDL_CreateRenderer");

    // On met le fond blanc
    resetBack(ui);
    SDL_RenderPresent(ui.renderer);

    // On initialise tout les boutons
    initButons(ui);

    // On affiche la page de commencement
    sdlInterface_start(ui);

    return ui;
}

/**
 * @brief Met a jour le plateau de jeu en mettant le pion de la couleur du
 * joueur en position (x,y)
 * @param ui l'interface
 * @param x la position en x dans le tableau (pas dans la fenetre)
 * @param y la position en y dans le tableau (pas dans la fenetre)
 * @param player le joueur (X ou O)
 */
void updateBoard(userInterface ui, int x, int y, Player player) {
    // On choisie la couleur du pion selon le joueur
    if (player == CROIX) {
        SDL_SetRenderDrawColor(ui.renderer, 255, 0, 0, 255);
    } else if (player == ROND) {
        SDL_SetRenderDrawColor(ui.renderer, 255, 255, 0, 255);
    }
    // On passe en coordonnées de la fenetre
    x *= CASE;
    y *= CASE;
    // On récupère le rayon du pion et la position du milieu
    int radus = CASE * 30;
    int midX = x + CASE / 2;
    int midY = y + CASE / 2;

    // On dessine le pion en faisant un cercle
    for (int i = y + 1; i < y + CASE - 1; i++) {
        for (int j = x + 1; j < x + CASE - 1; j++) {
            if ((midY - i) * (midY - i) + (midX - j) * (midX - j) < radus) {
                SDL_RenderDrawLine(ui.renderer, midY, midX, i, j);
            }
        }
    }
    SDL_RenderPresent(ui.renderer);
}

/**
 * @brief Attend que le mode de jeu et la difficulté de l'ia soit choisi pour la
 * sdl
 * @param game Le jeu
 * @param ui L'interface
 * @return 1 si on quitte, 0 sinon
 */
int choixModeEtIa(Puissance *game, userInterface ui) {
    SDL_Event event;
    int x, y, fini = 0;
    // On affiche le plateau de jeu et les boutons
    sdlInterface_printBoard(ui);
    // Lecture des évènements sur les boutons
    while (SDL_WaitEvent(&event) > 0 && !fini) {
        // On regarde si on quitte
        if (event.type == SDL_QUIT) return 1;
        // On regarde si on clique
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // On récupère la position de la souris
            SDL_GetMouseState(&x, &y);
            // On parcours les boutons de la page
            for (int i = 1; i < NB_BTN; i++) {
                // On regarde si on est sur un bouton
                if (test_estDansBtn(ui, x, y, i)) {
                    // Si oui on regard le quel et on agit en conséquence
                    if (i == 3) {
                        // L'utilisateur a choisi Joueur contre Joueur
                        // S'il avait déjà choisi un mode on le désélectionne
                        if (game->joueur != -1)
                            setColor(ui, game->joueur, COLOR_BACK_NOT_CLICK);
                        // On met le mode à jour
                        game->joueur = 3;
                        // On met le bouton en relief pour montrer la selection
                        setColor(ui, i, COLOR_BACK_IS_CLICK);
                        // On quitte la boucle pour jouer
                        return 0;
                    } else if (i == 1 || i == 2) {
                        // L'utilisateur a choisi un mode avec une IA
                        // S'il avait déjà choisi un mode on le désélectionne
                        if (game->joueur != -1)
                            setColor(ui, game->joueur, COLOR_BACK_NOT_CLICK);
                        // On met le mode à jour
                        game->joueur = i;
                        // On met le bouton en relief pour montrer la selection
                        setColor(ui, i, COLOR_BACK_IS_CLICK);
                    } else if ((i == 4 || i == 5 || i == 6) &&
                               game->joueur >= 0) {
                        // Suite au choix d'un mode de jeu avec IA,
                        // l'utilisateur choisi la dificulté
                        // On met la difficulté à jour
                        game->ia = i - 3;
                        // On met le bouton en relief pour montrer la selection
                        setColor(ui, i, COLOR_BACK_IS_CLICK);
                        // On quitte la boucle pour jouer
                        return 0;
                    } else if (i == 7) {
                        // L'utilisateur a choisi de revoir les règles
                        // S'il avait déjà choisi un mode on le réinitialise
                        if (game->joueur != -1) {
                            setColor(ui, game->joueur, COLOR_BACK_NOT_CLICK);
                            game->joueur = -1;
                        }
                        // On ré-affiche les règles
                        sdlInterface_start(ui);
                        // Astuce pour ne pas avoir des boucle dans des boucles
                        fini = 1;
                    }
                }
            }
        }
    }
    // On le fait seulement si on relis les règles
    return choixModeEtIa(game, ui);
}