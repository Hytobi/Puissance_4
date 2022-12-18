/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 24/11/2022
 * @brief: Ferme correctement le programme s'il y a une erreur dans la SDL
 * @file: rage.h
 */

#ifndef RAGE_H
#define RAGE_H

#include "SDL2/SDL.h"

/**
 * @brief Ferme correctement le programme s'il y a une erreur dans la SDL
 */
#define RAGE_QUIT(ui, msg)                                         \
    {                                                              \
        fprintf(stderr, "Erreur %s : %s", msg, SDL_GetError());    \
        if (NULL != ui.renderer) SDL_DestroyRenderer(ui.renderer); \
        if (NULL != ui.window) SDL_DestroyWindow(ui.window);       \
        if (NULL != ui.buttons) free(ui.buttons);                  \
        SDL_Quit();                                                \
        exit(EXIT_FAILURE);                                        \
    }

#endif