#include <stdint.h>

#include "parameters.h"
#include "parameters_repr.h"

// Version constants: used for stamp versions.
#define VERSION_MAJOR	(1)
#define VERSION_MINOR	(7)
#define FULL_VERSION (((VERSION_MINOR)%10) << 24) + ( ((VERSION_MINOR/10)%10) << 16) + (((VERSION_MINOR)/100) << 8) + VERSION_MAJOR

// init flag value constant
#define INIT_FLAG_VALUE		(0x1001BEEF)

// Declare const array for maximum limits of parameters (don't forget they are SIGNED INT)
const int32_t maxLim[PARAM_NUM] = {
	[PARAM_NONE] = 0,
	[PARAM_INIT_FLAG] = 0x7FFFFFFF,
    [PARAM_VERSION_MAJ] = 0x7FFFFFFF,
    [PARAM_VERSION_MIN] = 0x7FFFFFFF,

    [PARAM_SELECTOR_1] = SELECTOR_1_VALUE_NUM - 1,
    [PARAM_SELECTOR_2] = SELECTOR_2_VALUE_NUM - 1,

    [PARAM_SIMPLE_1] = 0xFFFF,
	[PARAM_SIMPLE_2] = 100,
};
// Declare const array for minimum limits of parameters
const int32_t minLim[PARAM_NUM] = {
	[PARAM_NONE] = 0,
	[PARAM_INIT_FLAG] = 0,
    [PARAM_VERSION_MAJ] = 0,
    [PARAM_VERSION_MIN] = 0,

    [PARAM_SELECTOR_1] = SELECTOR_1_SW1,
    [PARAM_SELECTOR_2] = SELECTOR_2_SW1,

    [PARAM_SIMPLE_1] = 0,
	[PARAM_SIMPLE_2] = 1,
};
// Declare const array for step of inc/dec of selector parameters
const uint32_t steps[PARAM_NUM] = {
    [PARAM_NONE] = 0,
	[PARAM_INIT_FLAG] = 0,
    [PARAM_VERSION_MAJ] = 0,
    [PARAM_VERSION_MIN] = 0,

    [PARAM_SELECTOR_1] = 1,
    [PARAM_SELECTOR_2] = 1,

    [PARAM_SIMPLE_1] = 0,
	[PARAM_SIMPLE_2] = 0,

};
// Declare const array for default values of parameters
const int32_t defaults[PARAM_NUM] = {
    [PARAM_NONE] = 0,
	[PARAM_INIT_FLAG] = INIT_FLAG_VALUE,
    [PARAM_VERSION_MAJ] = VERSION_MAJOR,
    [PARAM_VERSION_MIN] = VERSION_MINOR,

    [PARAM_SELECTOR_1] = SELECTOR_1_SW2,
    [PARAM_SELECTOR_2] = SELECTOR_2_SW3,

    [PARAM_SIMPLE_1] = 50,
	[PARAM_SIMPLE_2] = 40,
};


// register repr functions for each parameter
void (*_repr[PARAM_NUM])(ParamVal value, char * out) = {
    [PARAM_NONE] = _repr_null_str,
	[PARAM_INIT_FLAG] = _repr_int_to_str,
    [PARAM_VERSION_MAJ] = _repr_int_to_str,
    [PARAM_VERSION_MIN] = _repr_int_to_str,

    [PARAM_SELECTOR_1] = _repr_select1_to_str,
    [PARAM_SELECTOR_2] = _repr_select2_to_str,

    [PARAM_SIMPLE_1] = _repr_int_to_str,
	[PARAM_SIMPLE_2] = _repr_int_to_str,
};


// Function for testing parameters bounds.
static ParamVal _test(ParamVal value, const int32_t maxLim, const int32_t minLim) {
    if (value._int > maxLim) {
        return (ParamVal)maxLim;
    }
    else if (value._int < minLim) {
        return (ParamVal)minLim;
    }
    else {
        return value;
    }
}

// Structure for single parameter.
typedef struct {
    ParamId id;
    ParamVal value;
} Parameter;
// Static variable with all information about system parameters
Parameter systemParams[PARAM_NUM];

// function for main initialization of system parameters (also need for restore defaults)
void param_init(void) {
    for (uint16_t id; id < PARAM_NUM; id++) {
        systemParams[id].id = id;
        systemParams[id].value._int = defaults[id];
    }
}

// repr function for getting representation of selected param from current RAM value
void param_repr(ParamId id, char * out) {
    // call registered repr functions and fill output buffer with string
    (*_repr[id])(systemParams[id].value, out);
}

// repr function for getting representation of selected param from random VAL
void param_repr_val(ParamId id, ParamVal val, char * out) {
    // call registered repr functions and fill output buffer with string
    (*_repr[id])(val, out);
}

ParamVal param_get(ParamId id) {
    return systemParams[id].value;
}

// Function to set any single parameter.
void param_set(ParamId id, ParamVal val) {
    // call test function to validate parameter
    val = _test(val, maxLim[id], minLim[id]);
    // update param in systemparam array
    systemParams[id].value = val;
}

// Function to set array of parameters.
void param_set_array(ParamId startId, uint8_t num, ParamVal * val) {
    for (uint8_t id = 0; id < num; id++) {
        param_set(startId + id, val[id]);
    }
}

// step function not modifies systemParams array, just return value with inc or dec step
ParamVal param_step(ParamId id, ParamVal tmpParam, int32_t dir) {
    // apply step to tmpParam, if step is zero, then tmpParam not changed
    tmpParam._int += (dir * steps[id]);
    // run testing of incoming parameter and return results of bounding
    return _test(tmpParam, maxLim[id], minLim[id]);
}

