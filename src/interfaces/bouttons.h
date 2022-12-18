/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 16/12/2022
 * @brief: Gère les bouttons de la SDL
 * @file: bouttons.h
 */

#ifndef BOUTTONS_H
#define BOUTTONS_H

#include "SDL2/SDL.h"
#include "sldInterface.h"
#include "userInterface.h"

#define NB_BTN 8
#define W_BUTTON 100
#define H_BUTTON 50
#define X_BUTTON W_WINDOW - W_BUTTON - 20
#define X_MODE 55
#define X_DIFFICULTE 2 * CASE + X_MODE
#define ESPACE 60

#define COLOR_BTN_JOUEUR \
    (SDL_Color) { 231, 62, 1, 255 }
#define COLOR_BTN_IA \
    (SDL_Color) { 0, 255, 0, 255 }
#define COLOR_BTN_UTIL \
    (SDL_Color) { 255, 0, 0, 255 }
#define COLOR_BTN_IS_CLICK \
    (SDL_Color) { 0, 0, 0, 255 }
#define COLOR_BLANK \
    (SDL_Color) { 255, 255, 255, 255 }

void initButtons(userInterface ui);
int test_estDansBtn(userInterface ui, int x, int y, int i);
void affiche_btn(userInterface ui, int i);
void setColor(userInterface ui, int i, SDL_Color c);
#endif