/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 16/12/2022
 * @brief: Gère les boutons de la SDL
 * @file: boutons.h
 */

#ifndef BOUTONS_H
#define BOUTONS_H

#include "../userInterface.h"
#include "SDL2/SDL.h"
#include "sldInterface.h"

// Nombre de boutons
#define NB_BTN 8
// Taille des boutons
#define W_BUTTON 100
#define H_BUTTON 50
// Position x des boutons
#define X_BUTTON W_WINDOW - W_BUTTON - 20
// Position y des boutons de mode
#define Y_MODE 55
#define Y_DIFFICULTE 2 * CASE + Y_MODE
// L'espace entre les boutons
#define ESPACE 60
// Taille des images des boutons de mode
#define W_IMG 97
#define H_IMG 47

#define COLOR_BACK_IS_CLICK \
    (SDL_Color) { 0, 0, 0, 255 }
#define COLOR_BACK_NOT_CLICK \
    (SDL_Color) { 255, 255, 255, 255 }

/*
 ---------------------------
 Fonction utils pour le main
 ---------------------------
*/

/**
 * @brief Initialise les boutons de l'interface
 * @param ui l'interface
 */
void initButons(userInterface ui);

/**
 * @brief Test si la souris est dans le bouton i
 * @param ui l'interface
 * @param x coordonnée x de la souris
 * @param y coordonnée y de la souris
 * @param i l'indice du bouton à tester
 * @return 1 si la souris est dans le bouton, 0 sinon
 */
int test_estDansBtn(userInterface ui, int x, int y, int i);

/**
 * @brief Affiche le bouton sur l'interface
 * @param ui l'interface
 * @param i l'indice du bouton
 */
void affiche_btn(userInterface ui, int i);

/**
 * @brief Set la couleur arrière du bouton i
 * @param ui l'inteface
 * @param i l'indice du bouton à modifier
 * @param c La nouvelle couleur
 */
void setColor(userInterface ui, int i, SDL_Color c);

/**
 * @brief Set la couleur arrière de tous les boutons à la couleur par défaut
 * @param ui l'interface
 */
void resetColor(userInterface ui);

/*
 -----------------------------
 Fonction utils pour les tests
 -----------------------------
*/

/**
 * @brief Crée un bouton dans une interface SDL
 * @param ui l'interface
 * @param y coordonnée y du bouton
 * @param c La couleur du bouton
 * @return Bouton
 */
Bouton createButon(userInterface ui, int y, SDL_Color c);

/**
 * @brief Initialise les images sur les boutons
 * @param ui l'interface
 * @param i l'indice du bouton
 * @return SDL_Surface* l'image du bouton
 */
SDL_Surface* img_bouton(userInterface ui, int i);

#endif
