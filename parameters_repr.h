#ifndef PARAMETERS_REPR_H_INCLUDED
#define PARAMETERS_REPR_H_INCLUDED

#include "parameters.h"

// max buffer size to repr functions (without '\0' byte)
#define REPR_BUFFER_MAX_SIZE    (16)

typedef void (* pfn_repr)(ParamVal value, char * out);

// representing of simple data to strings
void _repr_null_str(ParamVal value, char * out);
void _repr_int_to_str(ParamVal value, char * out);

// representing of selectors to strings
void _repr_select1_to_str(ParamVal value, char * out);
void _repr_select2_to_str(ParamVal value, char * out);

#endif // PARAMETERS_REPR_H_INCLUDED
