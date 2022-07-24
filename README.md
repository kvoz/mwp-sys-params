# mwp-sys-params
Minimal working project for managing (reading, writing) parameters of system with simple representation them to output.

### Features

1. No dynamic allocations, all data full static.
1. Supports managing parameters of two types: selectors and simple `int`.
1. Common way to expand parameter list for both types.
1. Safe call to set or get parameters values.

([back to top](#top))


### Limitations

1. Length of repr srting, it constant for all parameters adn is predefined in `parameters_repr.h`.


([back to top](#top))

### Usage

1. In `parameters.h` expand `ParamId` list and add selectors enumerators (if need).
1. In `parameters_repr.h` declare functions for representing of new selectors.
1. In `parameters_repr.c` define functions for representing of new selectors and arrays for selectors strings.
1. In `parameters.c` register new parameter through arrays `maxLim[], minLim[], steps[], defaults[], _repr[]`.


([back to top](#top))