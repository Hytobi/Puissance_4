#include <CUnit/Basic.h>

#include "interfaces/sdl/test_sdlInterface.h"
#include "interfaces/text/test_textInterface.h"
#include "jouer_coup/test_jouer.h"
#include "jouer_coup/test_jouer_fin.h"
#include "jouer_coup/test_jouer_ia.h"

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    CU_ErrorCode error =
        CU_register_nsuites(3, getTestJouerSuites(), getTestJouerFinSuites(),
                            getTestJouerIaSuites());
    if (error != CUE_SUCCESS) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}