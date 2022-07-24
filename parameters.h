#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED

#include <stdint.h>

typedef enum {
    // Start dummy parameter, always zero
    PARAM_NONE,

    // Init flag holds status of first initialization of parameters
	PARAM_INIT_FLAG,

    // Version of FW (MAJ part)
    PARAM_VERSION_MAJ,
    // Version of FW (MIN part)
    PARAM_VERSION_MIN,

    // Selector parameters.
    PARAM_SELECTOR_1,
    PARAM_SELECTOR_2,

    // Simple parameters.
    PARAM_SIMPLE_1,
    PARAM_SIMPLE_2,

	// Total number of parameters, place another parameters above this line.
	PARAM_NUM
} ParamId;

// Values of parameter-selector_1
typedef enum {
    SELECTOR_1_SW1 = 0,
    SELECTOR_1_SW2,
    SELECTOR_1_SW3,
    SELECTOR_1_SW4,

    SELECTOR_1_VALUE_NUM
} ParamSelector1Value;

// Values of parameter-selector_2
typedef enum {
    SELECTOR_2_SW1 = 0,
    SELECTOR_2_SW2,
    SELECTOR_2_SW3,
    SELECTOR_2_SW4,

    SELECTOR_2_VALUE_NUM
} ParamSelector2Value;

typedef union paramVal_u {
    int32_t _int;
    float _float;
    uint8_t _compound[4];
} ParamVal;

void param_init(void);
void param_repr(ParamId id, char * out);
void param_repr_val(ParamId id, ParamVal val, char * out);
ParamVal param_get(ParamId id);
void param_set(ParamId id, ParamVal val);
void param_set_array(ParamId startId, uint8_t num, ParamVal * val);
ParamVal param_step(ParamId id, ParamVal tmpParam, int32_t dir);

#endif // PARAMETERS_H_INCLUDED
