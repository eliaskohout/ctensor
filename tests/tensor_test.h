#ifndef _TEST_TENSOR_H_INCLUDED_
#define _TEST_TENSOR_H_INCLUDED_


#include "../tensor.h"
#include "tensor_assert.h"


void tensor_test_is_empty(void);
void tensor_test_is_equal(void);
void tensor_test_check_size(void);
void tensor_test_set_size(void);
void tensor_test_set(void);
void tensor_test_get(void);
void tensor_test_init_one(void);
void tensor_test_init_zero(void);
void tensor_test_init_rand(void);
void tensor_test_cpy(void);
void tensor_test_add_inplace(void);
void tensor_test_sub_inplace(void);
void tensor_test_add(void);
void tensor_test_sub(void);

#endif // _TEST_TENSOR_H_INCLUDED_
