/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Implémente le back-end du jeu
 * @file: src/jouer_coup/jouer.c
 */

#include "jouer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../interfaces/sdl/boutons.h"
#include "SDL2/SDL.h"
#include "jouer_fin.h"
#include "jouer_ia.h"

/**
 * @brief Initialise le jeu
 * @param player Le joueur qui commence
 * @return Le jeu initialisé
 */
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

/**
 * @brief Cherche la ligne où jouer le coup dans la colonne col
 * @param p Le tableau du jeu
 * @param col La colonne dans la quelle jouer
 * @return la ligne où jouer le coup
 */
int chercheLigne(Player p[][NB_COLONNES], int col) {
    int l = 0;
    while (l < NB_LIGNES && p[l][col] == EMPTY) l++;
    return --l;
}

/**
 * @brief Met a jour le plateau de jeu sdl ou text avec un coup en [x,y]
 * @param game Le jeu
 * @param ui L'interface
 * @param x La colonne
 * @param y La ligne
 * @return 1 si le coup met fin a la partie, 0 sinon
 */
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

/**
 * @brief Traite les evenements du jeu en mode SDL
 * @param game le jeu
 * @param ui l'interface
 * @return 1 si l'utilisateur a quitté, 0 sinon
 */
int playSDL(Puissance* game, userInterface ui) {
    int x, y, fini = 0;
    SDL_Event event;

    // On attend que le mode de jeu et la difficulté de l'ia soit choisi
    fini = choixModeEtIa(game, ui);
    if (fini) return 1;
    // Si l'utilisateur n'a pas quitté on joue
    while (SDL_WaitEvent(&event) > 0 && !fini) {
        if (event.type == SDL_QUIT) return 1;
        // Si c'est le tour d'un joueur humain
        if ((game->joueur == 2 && game->player == CROIX) || game->joueur == 3) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // On recupere les coordonnées de la souris
                SDL_GetMouseState(&y, &x);
                // coordonnées souris -> coordonnées tableau
                y /= CASE;
                // Si la colonne est valide on joue le coup
                if (estColonneValide(game->board, y)) {
                    // On cherche la ligne où jouer le coup
                    x = chercheLigne(game->board, y);
                    // On joue le coup
                    fini = joueCoup(game, ui, x, y);
                }
            }
        } else {
            // Sinon c'est l'IA qui joue
            // On attend 2 secondes avant de jouer
            // SDL_Delay(2000);
            fini = pauseSDL();
            if (fini) return 1;

            //  Elle choisit la colonne où jouer
            y = chercheColonne(game);
            // On cherche la ligne où jouer le coup
            x = chercheLigne(game->board, y);
            // On joue le coup
            fini = joueCoup(game, ui, x, y);
        }
    }
    return 0;
}

/**
 * @brief Traite les evenements du jeu en mode texte
 * @param game le jeu
 * @param ui l'interface
 */
void playText(Puissance* game, userInterface ui) {
    int x, y, fini = 0, valide;
    // On affiche le tableau vide
    printBoard(game->board);
    while (!fini) {
        // Si c'est le tour d'un joueur humain
        if ((game->joueur == 2 && game->player == CROIX) || game->joueur == 3) {
            // Tant qu'on a pas de coordonnée valide on demande au joueur
            do {
                printf("Dans quelle colonne jouez-vous ? : ");
                if (!scanf("%d", &y)) {
                    printf("Entrez un nombre entre 0 et 6\n");
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
            // Sinon c'est l'IA qui joue
            // On attend 2 secondes avant de jouer
            sleep(2);
            // Elle choisit la colonne où jouer
            y = chercheColonne(game);
        }
        // Dans les 2 cas on cherche la ligne où jouer le coup
        x = chercheLigne(game->board, y);
        // On joue le coup
        fini = joueCoup(game, ui, x, y);
        valide = 0;
    }
}

/**
 * @brief Lance le jeu avec l'inteface choisie par l'utilisateur
 * @param game Le jeu
 * @param ui L'interface
 */
void puissance_playGame(Puissance* game, userInterface ui) {
    // Si le renderer est NULL, on joue en mode texte
    if (ui.renderer == NULL) {
        while (1) {
            // On demmande le mode de jeu et la difficulté de l'ia
            game->joueur = choosePlayer();
            if (game->joueur < 3) game->ia = dificulteIA();
            // On joue en mode texte
            playText(game, ui);
            // On demande si l'utilisateur veut rejouer
            if (rejouer() == 2) break;
            game = puissance_init(CROIX);
        }
    } else {
        // Sinon on joue en mode graphique
        while (1) {
            if (playSDL(game, ui)) break;
            resetColor(ui);
            sdlInterface_printBoard(ui);
            game = puissance_init(CROIX);
        }

        // Bien fermer la fenêtre SDL
        if (ui.renderer) SDL_DestroyRenderer(ui.renderer);
        if (ui.window) SDL_DestroyWindow(ui.window);
        if (ui.buttons) free(ui.buttons);
        SDL_Quit();
    }
}
