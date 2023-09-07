#ifndef _TESNORITER_TEST_H_INCLUDED_
#define _TESNORITER_TEST_H_INCLUDED_

#include "../tensor.h"
#include "../tensoriter.h"
#include "tensor_assert.h"

void tensoriter_test_scalar_next(void);
void tensoriter_test_scalar_get(void);
void tensoriter_test_scalar_set(void);
void tensoriter_test_scalar_map(void);
void tensoriter_test_scalar_map_add(void);
void tensoriter_test_scalar_map_sub(void);
void tensoriter_test_scalar_map_mul(void);
void tensoriter_test_scalar_map_div(void);

#endif // _TESNORITER_TEST_H_INCLUDED_
