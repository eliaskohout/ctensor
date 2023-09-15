#ifndef _TESNORITER_TEST_H_INCLUDED_
#define _TESNORITER_TEST_H_INCLUDED_

#include "../tensor.h"
#include "../tensorfunc.h"
#include "tensor_assert.h"


void tensor_test_fill(void);
void tensor_test_inspect(void);
void tensor_test_map(void);
void tensor_test_map_inplace(void);
void tensor_test_combine(void);
void tensor_test_combine_inplace(void);
void tensor_test_add_scalar(void);
void tensor_test_sub_scalar(void);
void tensor_test_mul_scalar(void);
void tensor_test_div_scalar(void);
void tensor_test_add_inplace(void);
void tensor_test_sub_inplace(void);
void tensor_test_mul_inplace(void);
void tensor_test_div_inplace(void);
void tensor_test_add(void);
void tensor_test_sub(void);
void tensor_test_mul(void);
void tensor_test_div(void);

#endif // _TESNORITER_TEST_H_INCLUDED_
