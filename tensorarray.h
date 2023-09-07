#ifndef _TENSORARRAY_H_INCLUDED_
#define _TENSORARRAY_H_INCLUDED_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "dtype.h"

inline bool tarray_equals(dtype* a1, dtype* a2, uint32_t len);
inline bool tarray_uint32_equals(uint32_t* a1, uint32_t* a2, uint32_t len);

#endif // _TENSORARRAY_H_INCLUDED_
