/** @author: PLOUVIN Patrice, PLOUVIN Patrick
 * @date: 02/12/2022
 * @brief: Fait les tests sur les fonctions de src/jouer_coup/jouer_fin.c
 * @file: test/jouer_coup/test_jouer_fin.c
 */

#include "test_jouer_fin.h"

#include "../../src/interfaces/userInterface.h"
#include "../../src/jouer_coup/jouer_fin.h"
#include "../tab.h"
#include "test_jouer.h"

/**
 * @brief Teste la fonction estColonneValide
 */
void test_estColonneValide(void) {
    // On crée un plateau de jeu vide
    Player p[NB_LIGNES][NB_COLONNES] = VIDE;
    // On regard c<0
    CU_ASSERT_EQUAL(estColonneValide(p, -1), 0);
    // On regarde c>6
    CU_ASSERT_EQUAL(estColonneValide(p, NB_COLONNES), 0);
    // On regarde c alant de 0 à 6 dans un tableau vide
    for (int i = 0; i < NB_COLONNES; i++) {
        CU_ASSERT_EQUAL(estColonneValide(p, i), 1);
    }
    // On regard c dans une colonne pleine (la 4eme)
    p[0][4] = CROIX;
    CU_ASSERT_EQUAL(estColonneValide(p, 4), 0);
}

/**
 * @brief Teste la fonction estPartiePleine
 */
void test_estPartiePleine(void) {
    // On crée un plateau de jeu vide
    Player p[NB_LIGNES][NB_COLONNES] = VIDE;
    // On regard si le plateau est plein
    CU_ASSERT_EQUAL(estPartiePleine(p), 0);

    // On crée un plateau de jeu plein
    Player p2[NB_LIGNES][NB_COLONNES] = CROSS;
    // On regarde si le plateau est plein
    CU_ASSERT_EQUAL(estPartiePleine(p2), 1);

    // On regard si ca fonctionne pour chaque colonne
    for (int c = 0; c < NB_COLONNES; c++) {
        p2[0][c] = EMPTY;
        CU_ASSERT_EQUAL(estPartiePleine(p2), 0);
        p2[0][c] = CROIX;
    }
}

/**
 * @brief  Teste la fonction estDansTab
 */
void test_estDansTab(void) {
    // Teste sur la ligne -1
    CU_ASSERT_EQUAL(estDansTab(-1, 0), 0);
    // Teste sur la colonne -1
    CU_ASSERT_EQUAL(estDansTab(0, -1), 0);
    // Teste sur la ligne 6
    CU_ASSERT_EQUAL(estDansTab(NB_LIGNES, 0), 0);
    // Teste sur la colonne 7
    CU_ASSERT_EQUAL(estDansTab(0, NB_COLONNES), 0);
    // Teste sur les tout le tableau
    for (int l = 0; l < NB_LIGNES; l++) {
        for (int c = 0; c < NB_COLONNES; c++) {
            CU_ASSERT_EQUAL(estDansTab(l, c), 1);
        }
    }
}

/**
 * @brief Teste la fonction compteValeur
 */
void test_compteValeur(void) {
    int l, c;
    // On crée un plateau de jeu vide
    Player p[NB_LIGNES][NB_COLONNES] = VIDE;
    // On regarde si la fonction compteValeur fonctionne
    p[0][0] = CROIX;
    CU_ASSERT_EQUAL(compteValeur(p, CROIX, 0, 0, 0, 0), 1);
    // Test compter en ligne
    for (c = 0; c < NB_COLONNES; c++) {
        p[0][c] = CROIX;
        CU_ASSERT_EQUAL(compteValeur(p, CROIX, 0, 0, 0, 1), c + 1);
    }
    // Test compter en colonne
    Player p2[NB_LIGNES][NB_COLONNES] = VIDE;
    for (l = 0; l < NB_LIGNES; l++) {
        p2[l][0] = CROIX;
        CU_ASSERT_EQUAL(compteValeur(p2, CROIX, 0, 0, 1, 0), l + 1);
    }
    // Test compter en diagonale
    Player p3[NB_LIGNES][NB_COLONNES] = VIDE;
    for (l = 0; l < NB_LIGNES; l++) {
        p3[l][l] = CROIX;
        CU_ASSERT_EQUAL(compteValeur(p3, CROIX, 0, 0, 1, 1), l + 1);
    }
    // Test compter en diagonale inverse
    Player p4[NB_LIGNES][NB_COLONNES] = VIDE;
    for (l = 0; l < NB_LIGNES; l++) {
        p4[l][NB_LIGNES - l - 1] = CROIX;
        CU_ASSERT_EQUAL(compteValeur(p4, CROIX, 0, NB_LIGNES - 1, 1, -1),
                        l + 1);
    }
}

/**
 * @brief Teste la fonction max
 */
void test_max(void) {
    // 4x3x2 = 24 cobinaisons
    CU_ASSERT_EQUAL(max(1, 2, 3, 4), 4);
    CU_ASSERT_EQUAL(max(1, 4, 3, 2), 4);
    CU_ASSERT_EQUAL(max(1, 2, 4, 3), 4);
    CU_ASSERT_EQUAL(max(1, 3, 2, 4), 4);
    CU_ASSERT_EQUAL(max(1, 3, 4, 2), 4);
    CU_ASSERT_EQUAL(max(1, 4, 2, 3), 4);
    CU_ASSERT_EQUAL(max(2, 1, 3, 4), 4);
    CU_ASSERT_EQUAL(max(2, 1, 4, 3), 4);
    CU_ASSERT_EQUAL(max(2, 3, 1, 4), 4);
    CU_ASSERT_EQUAL(max(2, 3, 4, 1), 4);
    CU_ASSERT_EQUAL(max(2, 4, 1, 3), 4);
    CU_ASSERT_EQUAL(max(2, 4, 3, 1), 4);
    CU_ASSERT_EQUAL(max(3, 1, 2, 4), 4);
    CU_ASSERT_EQUAL(max(3, 1, 4, 2), 4);
    CU_ASSERT_EQUAL(max(3, 2, 1, 4), 4);
    CU_ASSERT_EQUAL(max(3, 2, 4, 1), 4);
    CU_ASSERT_EQUAL(max(3, 4, 1, 2), 4);
    CU_ASSERT_EQUAL(max(3, 4, 2, 1), 4);
    CU_ASSERT_EQUAL(max(4, 1, 2, 3), 4);
    CU_ASSERT_EQUAL(max(4, 1, 3, 2), 4);
    CU_ASSERT_EQUAL(max(4, 2, 1, 3), 4);
    CU_ASSERT_EQUAL(max(4, 2, 3, 1), 4);
    CU_ASSERT_EQUAL(max(4, 3, 1, 2), 4);
    CU_ASSERT_EQUAL(max(4, 3, 2, 1), 4);
}

// Pas de test cGagné car utilise compteValeur et  max
// Pas de test verifFinPartie car utilise cGagné et estPartiePleine

// Liste des tests
static CU_TestInfo test_array[] = {
    {" test_estColonneValide ", test_estColonneValide},
    {" test_estPartiePleine ", test_estPartiePleine},
    {" test_estDansTab ", test_estDansTab},
    {" test_max ", test_max},
    CU_TEST_INFO_NULL};

// Liste des suites de test
static CU_SuiteInfo suites[2] = {
    {"suite_jouer_fin", NULL, NULL, NULL, NULL, test_array},
    CU_SUITE_INFO_NULL};

/**
 * @brief Récupère les suites de test de src/jouer_coup/jouer_fin.c
 * @return CU_SuiteInfo*
 */
CU_SuiteInfo* getTestJouerFinSuites() { return suites; }