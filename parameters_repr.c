#include "parameters_repr.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// TODO: choose better call in _repr_int_to_str() : sprintf or itoa

// Constant strings for parameter with selection type
const char * selector1_repr_values[] = {
    [SELECTOR_1_SW1] = "SEL1 - SW1",
    [SELECTOR_1_SW2] = "SEL1 - SW2",
    [SELECTOR_1_SW3] = "SEL1 - SW3",
    [SELECTOR_1_SW4] = "SEL1 - SW4",
};

const char * selector2_repr_values[] = {
    [SELECTOR_2_SW1] = "SEL2 - SW1",
    [SELECTOR_2_SW2] = "SEL2 - SW2",
    [SELECTOR_2_SW3] = "SEL2 - SW3",
    [SELECTOR_2_SW4] = "SEL2 - SW4",
};

// function for representation of parameters
void _repr_null_str(ParamVal value, char * out) {
    memset(out, 0, REPR_BUFFER_MAX_SIZE);
}

void _repr_int_to_str(ParamVal value, char * out) {
//    sprintf(out, "%d", value._int);
    itoa(value._int, out, 10);
}

// private functions for representing of selectors to strings
void _repr_select1_to_str(ParamVal value, char * out) {
    uint16_t sLen = 0;

    sLen = strlen(selector1_repr_values[value._int]);

    if (sLen > REPR_BUFFER_MAX_SIZE) {
        sLen = REPR_BUFFER_MAX_SIZE;
    }

    memcpy(out, selector1_repr_values[value._int], sLen);
    out[sLen] = 0;
}

// private functions for representing of selectors to strings
void _repr_select2_to_str(ParamVal value, char * out) {
    uint16_t sLen = 0;

    sLen = strlen(selector2_repr_values[value._int]);

    if (sLen > REPR_BUFFER_MAX_SIZE) {
        sLen = REPR_BUFFER_MAX_SIZE;
    }

    memcpy(out, selector2_repr_values[value._int], sLen);
    out[sLen] = 0;
}

