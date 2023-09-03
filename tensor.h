#ifndef _TENSOR_H_INCLUDED_
#define _TENSOR_H_INCLUDED_

#include "dtype.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct _tensor {
	dtype *elements;
	uint8_t rank;
	uint32_t *size;
	uint32_t *index_offsets;
	uint32_t num_elem;
} *tensor;


tensor tensor_new(void);
void tensor_destroy(tensor t);

bool tensor_is_empty(const tensor t);
bool tensor_is_equal(const tensor t1, const tensor t2);

bool _tensor_check_size(const uint32_t *size, uint8_t rank);
bool _tensor_set_size(tensor t, const uint32_t *size, uint8_t rank);

bool tensor_set(tensor t, const uint32_t *index, dtype val);
dtype tensor_get(const tensor t, const uint32_t *index, bool *success);

bool tensor_init_one(tensor t, const uint32_t *size, uint8_t rank);
bool tensor_init_zero(tensor t, const uint32_t *size, uint8_t rank);
bool tensor_init_rand(tensor t, const uint32_t *size, uint8_t rank, dtype max);
bool tensor_cpy(tensor t1, const tensor t2);

bool tensor_add_inplace(tensor t1, const tensor t2);
bool tensor_sub_inplace(tensor t1, const tensor t2);
tensor tensor_add(const tensor t1, const tensor t2);
tensor tensor_sub(const tensor t1, const tensor t2);

void tensor_print(const tensor t);

#endif
