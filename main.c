#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "parameters.h"

#include <windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Load all parameters to default.
    param_init();

    /* each cyrillic  symbol equals:
        - 1 byte in windows-1251
        - 2 bytes in UTF-8
    */
    char outX[50] = {0};
    ParamVal shadowParam;

    for (int i = PARAM_INIT_FLAG; i < PARAM_NUM; i++) {
        shadowParam = param_get(i);
        param_repr_val(i, shadowParam, outX);
        printf("[%d] - %s\n", i, outX);
    }

    printf("\n------\n");

    ParamVal newPar;
    newPar._int = 1999;

    param_set(PARAM_INIT_FLAG, newPar);

    shadowParam = param_get(PARAM_INIT_FLAG);
    param_repr_val(PARAM_INIT_FLAG, shadowParam, outX);
    printf("Parameter [%d] set to %s\n\n", PARAM_INIT_FLAG, outX);

    for (int i = PARAM_INIT_FLAG; i < PARAM_NUM; i++) {
        shadowParam = param_get(i);
        param_repr_val(i, shadowParam, outX);
        printf("[%d] - %s\n", i, outX);
    }

    printf("\n--- CHECK SELECTOR 1 (change and apply) ---\n");

    uint32_t parID = PARAM_SELECTOR_1;
    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Selected param ID %d, with repr: %s\n", parID, outX);

    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Entered to selector, repr val is: %s\n", outX);

    shadowParam = param_step(parID, shadowParam, +1);
    param_repr_val(parID, shadowParam, outX);
    printf("INC selector, repr val is: %s\n", outX);

    shadowParam = param_step(parID, shadowParam, -1);
    param_repr_val(parID, shadowParam, outX);
    printf("DEC 1 selector, repr val is: %s\n", outX);

    shadowParam = param_step(parID, shadowParam, -1);
    param_repr_val(parID, shadowParam, outX);
    printf("DEC 2 selector, repr val is: %s\n", outX);

    param_set(parID, shadowParam);
    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Save selector, repr val is: %s\n", outX);

    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Afterall param ID %d, with repr: %s\n", parID, outX);

    printf("\n--- CHECK SELECTOR 2 (change and escape) ---\n");

    parID = PARAM_SELECTOR_2;
    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Selected param ID %d, with repr: %s\n", parID, outX);

    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Entered to selector, repr val is: %s\n", outX);

    shadowParam = param_step(parID, shadowParam, +1);
    param_repr_val(parID, shadowParam, outX);
    printf("INC 1 selector, repr val is: %s\n", outX);

    shadowParam = param_step(parID, shadowParam, +1);
    param_repr_val(parID, shadowParam, outX);
    printf("INC 2 selector, repr val is: %s\n", outX);

    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Escape selector, repr val is: %s\n", outX);

    shadowParam = param_get(parID);
    param_repr_val(parID, shadowParam, outX);
    printf("Afterall param ID %d, with repr: %s\n", parID, outX);

    return 0;
}
