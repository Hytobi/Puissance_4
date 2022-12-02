#include "test_jouer_fin.h"

#include "../src/jouer_fin.h"
#include "../src/userInterface.h"
#include "tab.h"
#include "test_jouer.h"

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
    // On regard c dans une colonne pleine
    p[0][4] = CROIX;
    CU_ASSERT_EQUAL(estColonneValide(p, 4), 0);
}

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

void test_estDansTab(void) {
    CU_ASSERT_EQUAL(estDansTab(-1, 0), 0);
    CU_ASSERT_EQUAL(estDansTab(0, -1), 0);
    CU_ASSERT_EQUAL(estDansTab(NB_LIGNES, 0), 0);
    CU_ASSERT_EQUAL(estDansTab(0, NB_COLONNES), 0);
    for (int l = 0; l < NB_LIGNES; l++) {
        for (int c = 0; c < NB_COLONNES; c++) {
            CU_ASSERT_EQUAL(estDansTab(l, c), 1);
        }
    }
}

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
    /* a voir si on garde ce test
    // En partant de l = NB_LIGNES - 1 en diagonale
    Player p5[NB_LIGNES][NB_COLONNES] = {EMPTY};
    for (l = NB_LIGNES - 1; l >= 0; l--) {
        p5[l][l] = CROIX;
        CU_ASSERT_EQUAL(compteValeur(p5, CROIX, NB_LIGNES - 1, NB_LIGNES - 1,
    -1, -1), NB_LIGNES - l);
    }
    // En partant de l = NB_LIGNES - 1 en diagonale inverse
    Player p6[NB_LIGNES][NB_COLONNES] = {EMPTY};
    for (l = NB_LIGNES - 1; l >= 0; l--) {
        p6[l][NB_LIGNES - l - 1] = CROIX;
        CU_ASSERT_EQUAL(compteValeur(p6, CROIX, NB_LIGNES - 1, 0, -1, 1),
    NB_LIGNES - l);
    }
    */
}

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

static CU_TestInfo test_array[] = {
    {" test_estColonneValide ", test_estColonneValide},
    {" test_estPartiePleine ", test_estPartiePleine},
    {" test_estDansTab ", test_estDansTab},
    {" test_max ", test_max},
    CU_TEST_INFO_NULL};

static CU_SuiteInfo suites[2] = {
    {"suite_jouer_fin", NULL, NULL, NULL, NULL, test_array},
    CU_SUITE_INFO_NULL};
CU_SuiteInfo* getTestJouerFinSuites() { return suites; }