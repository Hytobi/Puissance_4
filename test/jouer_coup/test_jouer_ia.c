#include "test_jouer_ia.h"

#include "../../src/jouer_coup/jouer_ia.h"
#include "../../src/interfaces/userInterface.h"
#include "../tab.h"
#include "test_jouer.h"

void test_prochainCoupGagne(void) {
    Player p[NB_LIGNES][NB_COLONNES] = VIDE;
    // Au début, il n'y a pas de coup gagnant
    CU_ASSERT_EQUAL(prochainCoupGagne(p, ROND), -1);
    // Test gagner en ligne
    p[NB_LIGNES - 1][2] = CROIX;
    p[NB_LIGNES - 1][4] = CROIX;
    p[NB_LIGNES - 1][5] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p, CROIX), 3);

    // Test gagner en colonne
    Player p2[NB_LIGNES][NB_COLONNES] = VIDE;
    p2[NB_LIGNES - 1][2] = CROIX;
    p2[NB_LIGNES - 2][2] = CROIX;
    p2[NB_LIGNES - 3][2] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p2, CROIX), 2);
    // Test gagner en diagonale
    Player p3[NB_LIGNES][NB_COLONNES] = VIDE;
    p3[NB_LIGNES - 1][2] = CROIX;
    p3[NB_LIGNES - 1][3] = ROND;
    p3[NB_LIGNES - 3][4] = CROIX;
    p3[NB_LIGNES - 4][5] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p3, CROIX), 3);

    // Test gagner en diagonale inverse
    Player p4[NB_LIGNES][NB_COLONNES] = VIDE;
    p4[NB_LIGNES - 4][2] = CROIX;
    p4[NB_LIGNES - 2][3] = ROND;
    p4[NB_LIGNES - 2][4] = CROIX;
    p4[NB_LIGNES - 1][5] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p4, CROIX), 3);
}

void test_coupAdversaire(void) {
    Player p[NB_LIGNES][NB_COLONNES] = VIDE;
    // Au debut (size >= 6) -> colonne dans {2,3,4}
    // (|actual−expected|≤|granularity|)
    CU_ASSERT_DOUBLE_EQUAL(coupAdversaire(p, ROND), 2, 2);

    // Si la partie est pleine on retourne -1
    Player p2[NB_LIGNES][NB_COLONNES] = CROSS;
    CU_ASSERT_EQUAL(coupAdversaire(p2, ROND), -1);
}

static CU_TestInfo test_array[] = {
    {" test_prochainCoupGagne ", test_prochainCoupGagne},
    {" test_coupAdversaire ", test_coupAdversaire},
    CU_TEST_INFO_NULL};

static CU_SuiteInfo suites[2] = {
    {"suite_jouer_ia", NULL, NULL, NULL, NULL, test_array}, CU_SUITE_INFO_NULL};
CU_SuiteInfo* getTestJouerIaSuites() { return suites; }