#include "../src/jouer_ia.h"
#include "../src/userInterface.h"
#include "test_jouer.h"

void test_prochainCoupGagne(void) {
    Player p[NB_LIGNES][NB_COLONNES] = {EMPTY};
    // Au début, il n'y a pas de coup gagnant
    CU_ASSERT_EQUAL(prochainCoupGagne(p, ROND), -1);
    // Test gagner en ligne
    p[NB_LIGNES - 1][2] = CROIX;
    p[NB_LIGNES - 1][4] = CROIX;
    p[NB_LIGNES - 1][5] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p, CROIX), 3);

    // Test gagner en colonne
    Player p2[NB_LIGNES][NB_COLONNES] = {EMPTY};
    p2[NB_LIGNES - 1][2] = CROIX;
    p2[NB_LIGNES - 2][2] = CROIX;
    p2[NB_LIGNES - 3][2] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p2, CROIX), 2);
    // Test gagner en diagonale
    Player p3[NB_LIGNES][NB_COLONNES] = {EMPTY};
    p3[NB_LIGNES - 1][2] = CROIX;
    p3[NB_LIGNES - 1][3] = ROND;
    p3[NB_LIGNES - 3][4] = CROIX;
    p3[NB_LIGNES - 4][5] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p3, CROIX), 3);

    // Test gagner en diagonale inverse
    Player p4[NB_LIGNES][NB_COLONNES] = {EMPTY};
    p3[NB_LIGNES - 4][2] = CROIX;
    p3[NB_LIGNES - 2][3] = ROND;
    p3[NB_LIGNES - 2][4] = CROIX;
    p3[NB_LIGNES - 1][5] = CROIX;
    CU_ASSERT_EQUAL(prochainCoupGagne(p3, CROIX), 3);
}

int coupAdversaire(Player p[][NB_COLONNES], Player joueur) {
    int l, c, t, js, max = 0, size = 0;
    int tab[NB_COLONNES] = {-1};

    // Comme je joue le coup de l'adversaire le pb est la
    Player joueurSuivant = (joueur == ROND) ? CROIX : ROND;

    // On teste tous les coups possibles
    for (c = 0; c < NB_COLONNES; c++) {
        // Si la colonne est pleine on passe au coup suivant
        if (p[0][c] != EMPTY) continue;

        // On cherche la ligne pour se placer
        l = chercheLigne(p, c);

        // On joue le coup de l'adversaire
        p[l][c] = joueurSuivant;

        // Si il aligne plus de pions que precedemment
        if ((t = cGagne(p, joueurSuivant, l, c)) >= max) {
            // js est le nombre de pions alignés par l'adversaire au coup
            // suivant si je joue el (l,c)

            // Cette partie du code :
            // https://www.instagram.com/reel/Ckkq2nCJNq5/?igshid=YmMyMTA2M2Y=
            // p[l - 1][c] = joueur;
            js = cGagne(p, joueur, l - 1, c);
            printf("js = %d et c=%d\n", js, c);
            // p[l - 1][c] = EMPTY;

            // Si il trouve un meilleur coup que le précédent
            // On remet le tableau à 0
            if (t > max && js < 3) {
                size = 0;
                tab[size++] = c;
                max = t;
                // printf("\nNouveau tab et j'ajoute %d ", c);
            } else {
                // On ajoute le coup dans le tableau si le prochain joueur ne
                // peut pas aligné 3 pions grace a nous
                if (js < 3) {
                    // printf("%d ", c);
                    tab[size++] = c;
                }
            }
        }
        p[l][c] = EMPTY;
    }
    // Si on a trop de coup a jouer on joue au centre
    if (size >= 6) {
        // colonne dans {2,3,4}
        return (rand() % 3) + 2;
    }
    if (size) return tab[rand() % size];
    return -1;
}

void test_coupAdversaire(void) {
    Player p[NB_LIGNES][NB_COLONNES] = {EMPTY};
    // Au debut (size >= 6) -> colonne dans {2,3,4}
    // (|actual−expected|≤|granularity|)
    CU_ASSERT_DOUBLE_EQUAL(coupAdversaire(p, ROND), 2, 2);

    // Si la partie est pleine on retourne -1
    Player p2[NB_LIGNES][NB_COLONNES] = {CROIX};
    CU_ASSERT_EQUAL(coupAdversaire(p2, ROND), -1);
}

static CU_TestInfo test_array[] = {
    {" test_prochainCoupGagne ", test_prochainCoupGagne},
    {" test_coupAdversaire ", test_coupAdversaire},
    CU_TEST_INFO_NULL};

static CU_SuiteInfo suites[2] = {{"suite", NULL, NULL, NULL, NULL, test_array},
                                 CU_SUITE_INFO_NULL};
CU_SuiteInfo* getTestJouerIaSuites() { return suites; }