/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 02/12/2022
 * @brief: Initialise les tableaux remplis de Player
 * @file: test/tab.h
 */

#ifndef TAB_H
#define TAB_H

#include "../src/interfaces/userInterface.h"

// Tableaux de Player remplis de EMPTY
#define VIDE                                                     \
    {                                                            \
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},       \
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},   \
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},   \
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},   \
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, { \
            EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY      \
        }                                                        \
    }

// Tableaux de Player remplis de CROIX
#define CROSS                                                    \
    {                                                            \
        {CROIX, CROIX, CROIX, CROIX, CROIX, CROIX, CROIX},       \
            {CROIX, CROIX, CROIX, CROIX, CROIX, CROIX, CROIX},   \
            {CROIX, CROIX, CROIX, CROIX, CROIX, CROIX, CROIX},   \
            {CROIX, CROIX, CROIX, CROIX, CROIX, CROIX, CROIX},   \
            {CROIX, CROIX, CROIX, CROIX, CROIX, CROIX, CROIX}, { \
            CROIX, CROIX, CROIX, CROIX, CROIX, CROIX, CROIX      \
        }                                                        \
    }

// Tableaux de Player remplis de ROND
#define CERCLE                                            \
    {                                                     \
        {ROND, ROND, ROND, ROND, ROND, ROND, ROND},       \
            {ROND, ROND, ROND, ROND, ROND, ROND, ROND},   \
            {ROND, ROND, ROND, ROND, ROND, ROND, ROND},   \
            {ROND, ROND, ROND, ROND, ROND, ROND, ROND},   \
            {ROND, ROND, ROND, ROND, ROND, ROND, ROND}, { \
            ROND, ROND, ROND, ROND, ROND, ROND, ROND      \
        }                                                 \
    }

#endif