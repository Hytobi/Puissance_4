#include "test_jouer.h"

#include "../src/jouer.h"
#include "../src/userInterface.h"
#include "tab.h"

void test_chercheLigne(void) {
    Player p[NB_LIGNES][NB_COLONNES] = VIDE;
    for (int l = NB_LIGNES - 1; l >= 0; l--) {
        for (int c = 0; c < NB_COLONNES; c++) {
            CU_ASSERT_EQUAL(chercheLigne(p, c), l);
            p[l][c] = CROIX;
        }
    }

    Player p2[NB_LIGNES][NB_COLONNES] = CROSS;
    for (int c = 0; c < NB_COLONNES; c++) {
        CU_ASSERT_EQUAL(chercheLigne(p2, c), -1);
    }
}

static CU_TestInfo test_array[] = {{" test_chercheLigne ", test_chercheLigne},
                                   CU_TEST_INFO_NULL};

static CU_SuiteInfo suites[2] = {
    {"suite_jouer", NULL, NULL, NULL, NULL, test_array}, CU_SUITE_INFO_NULL};
CU_SuiteInfo* getTestJouerSuites() { return suites; }