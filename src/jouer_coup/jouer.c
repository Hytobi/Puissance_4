/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente le back-end du jeu
 * @file: jouer.c
 */

#include "jouer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../interfaces/bouttons.h"
#include "SDL2/SDL.h"
#include "jouer_fin.h"
#include "jouer_ia.h"

Puissance* puissance_init(Player player) {
    Puissance* game = malloc(sizeof(Puissance));
    game->player = player;
    game->joueur = -1;
    game->ia = -1;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            // On met la grille à vide
            game->board[i][j] = EMPTY;
        }
    }
    return game;
}

int chercheLigne(Player p[][NB_COLONNES], int col) {
    int l = 0;
    while (l < NB_LIGNES && p[l][col] == EMPTY) l++;
    return --l;
}

int joueCoup(Puissance* game, userInterface ui, int x, int y) {
    // On joue le coup
    game->board[x][y] = game->player;
    // On met à jour l'affichage
    if (ui.renderer)
        updateBoard(ui, x, y, game->player);
    else
        printBoard(game->board);
    // On vérifie si la partie est finie
    return verifFinPartie(game, ui, x, y);
}

int choixModeEtIa(Puissance* game, userInterface ui) {
    SDL_Event event;
    int x, y, fini = 0;
    // On affiche le plateau de jeu
    sdlInterface_printBoard(ui);
    while (SDL_WaitEvent(&event) > 0 && !fini) {
        if (event.type == SDL_QUIT) return 1;
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&x, &y);
            for (int i = 1; i < NB_BTN; i++) {
                if (test_estDansBtn(ui, x, y, i)) {
                    if (i == 3) {
                        if (game->joueur != -1)
                            setColor(ui, game->joueur, COLOR_BTN_JOUEUR);
                        game->joueur = 3;
                        setColor(ui, i, COLOR_BTN_IS_CLICK);
                        return 0;
                    } else if (i == 1 || i == 2) {
                        if (game->joueur != -1)
                            setColor(ui, game->joueur, COLOR_BTN_JOUEUR);
                        game->joueur = i;
                        setColor(ui, i, COLOR_BTN_IS_CLICK);
                    } else if ((i == 4 || i == 5 || i == 6) &&
                               game->joueur >= 0) {
                        game->ia = i - 3;
                        setColor(ui, i, COLOR_BTN_IS_CLICK);
                        return 0;
                    } else if (i == 7) {
                        sdlInterface_start(ui);
                        fini = 1;
                    }
                }
            }
            // if (fini) break;
            //  peut etre mettre de sbreack et un fini=0 ??
            //  changer la couleur si on rechange de choix de mode ia
        }
    }
    choixModeEtIa(game, ui);
    // return 0;
}

// On joue
void playSDL(Puissance* game, userInterface ui) {
    int x, y, fini = 0;
    SDL_Event event;
    fini = choixModeEtIa(game, ui);
    while (SDL_WaitEvent(&event) > 0 && !fini) {
        if (event.type == SDL_QUIT) break;
        if ((game->joueur == 2 && game->player == CROIX) || game->joueur == 3) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // On recupere les coordonnées de la souris
                SDL_GetMouseState(&y, &x);
                // coordonnées souris -> coordonnées tableau
                y /= CASE;
                if (estColonneValide(game->board, y)) {
                    x = chercheLigne(game->board, y);
                    fini = joueCoup(game, ui, x, y);
                }
            }
        } else {
            SDL_Delay(2000);
            // Sinon on joue un coup aléatoire
            y = chercheColonne(game);
            x = chercheLigne(game->board, y);
            fini = joueCoup(game, ui, x, y);
        }
    }
}

void playText(Puissance* game, userInterface ui) {
    int x, y, fini = 0, valide;
    // On affiche le tableau vide
    printBoard(game->board);
    while (!fini) {
        // Si c'est le tour d'un joueur humain
        if ((game->joueur == 2 && game->player == CROIX) || game->joueur == 3) {
            // Tant qu'on a pas de coord valide on demande
            do {
                printf("Dans quelle colonne jouez-vous ? : ");
                if (!scanf("%d", &y)) {
                    printf("Format attendu : int\n");
                    videBuffer();
                    continue;
                };
                valide = estColonneValide(game->board, y);
                if (!valide) {
                    printf("Colonne pleine ou hors selection\n");
                    videBuffer();
                }
            } while (!valide);
        } else {
            sleep(2);
            y = chercheColonne(game);
        }
        x = chercheLigne(game->board, y);
        fini = joueCoup(game, ui, x, y);
    }
}

void puissance_playGame(Puissance* game, userInterface ui) {
    if (ui.renderer == NULL) {
        // Si y'a pas de renderer, on joue en mode texte
        game->joueur = choosePlayer();
        if (game->joueur < 3) game->ia = dificulteIA();
        playText(game, ui);
    } else {
        // Sinon on joue en mode graphique
        playSDL(game, ui);
    }

    // Bien fermer la fenêtre SDL
    if (NULL != ui.renderer) SDL_DestroyRenderer(ui.renderer);
    if (NULL != ui.window) SDL_DestroyWindow(ui.window);
    SDL_Quit();
}
// Fin on joue
