#include "test_jouer.h"

#include "../src/jouer.h"
#include "../src/userInterface.h"

void test_chercheLigne(void) {
    Player p[NB_LIGNES][NB_COLONNES] = {EMPTY};

    for (int i = 0; i < NB_COLONNES; i++) {
        CU_ASSERT_EQUAL(chercheLigne(p, i), 5);
        p[0][i] = CROIX;
        CU_ASSERT_EQUAL(chercheLigne(p, i), 4);
        p[1][i] = CROIX;
        CU_ASSERT_EQUAL(chercheLigne(p, i), 3);
        p[2][i] = CROIX;
        CU_ASSERT_EQUAL(chercheLigne(p, i), 2);
        p[3][i] = CROIX;
        CU_ASSERT_EQUAL(chercheLigne(p, i), 1);
        p[4][i] = CROIX;
        CU_ASSERT_EQUAL(chercheLigne(p, i), 0);
        p[5][i] = CROIX;
        CU_ASSERT_EQUAL(chercheLigne(p, i), -1);
    }
}

static CU_TestInfo test_array[] = {{" test_chercheLigne ", test_chercheLigne},
                                   CU_TEST_INFO_NULL};

static CU_SuiteInfo suites[2] = {{"suite", NULL, NULL, NULL, NULL, test_array},
                                 CU_SUITE_INFO_NULL};
CU_SuiteInfo* getTestJouerSuites() { return suites; }