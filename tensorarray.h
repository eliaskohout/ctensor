#ifndef _TENSORARRAY_H_INCLUDED_
#define _TENSORARRAY_H_INCLUDED_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "dtype.h"

bool tarray_equals(const dtype* a1, const dtype* a2, uint32_t len);
bool tarray_uint32_equals(const uint32_t* a1, const uint32_t* a2, uint32_t len);

#endif // _TENSORARRAY_H_INCLUDED_
