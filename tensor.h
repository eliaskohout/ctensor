#ifndef TENSOR_H_INCLUDED
#define TENSOR_H_INCLUDED

#include <_types/_uint32_t.h>
#include <_types/_uint8_t.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>

/* Defining the datatype of the tensor */
typedef float dtype;
/* dtype needs to implement add, sub, mul and div, */
#define DTYPE_ADD(a, b) ((a) + (b))
#define DTYPE_SUB(a, b) ((a) - (b))
#define DTYPE_MUL(a, b) ((a) * (b))
#define DTYPE_DIV(a, b) ((a) / (b))
/* equal and not equal,*/
#define DTYPE_EQ(a, b) ((a) == (b))
#define DTYPE_NE(a, b) ((a) != (b))
/* one and zero, */
#define DTYPE_ONE 1.0
#define DTYPE_ZERO 0.0
/* and a random and pruint8_t function */
#define DTYPE_RAND(max) ((float) rand() / RAND_MAX * (max))
#define DTYPE_PRINT(a) (printf(" %4.1f ", (a)))


typedef struct _tensor {
	dtype *elements;
	uint8_t rank;
	uint32_t *size;
	uint32_t *index_offsets;
	uint32_t num_elem;
} *tensor;


tensor tensor_new(void);
void tensor_destroy(tensor t);

uint8_t tensor_is_empty(const tensor t);
uint8_t tensor_is_equal(const tensor t1, const tensor t2);

uint8_t _tensor_check_size(const uint32_t *size, uint8_t rank);
uint8_t _tensor_set_size(tensor t, const uint32_t *size, uint8_t rank);

uint8_t tensor_set(tensor t, const uint32_t *index, dtype val);
dtype tensor_get(const tensor t, const uint32_t *index, uint8_t *success);

uint8_t tensor_init_one(tensor t, uint8_t rank, const uint32_t *size);
uint8_t tensor_init_zero(tensor t, uint8_t rank, const uint32_t *size);
uint8_t tensor_init_rand(tensor t, uint8_t rank, const uint32_t *size, dtype max);
uint8_t tensor_cpy(tensor t1, const tensor t2);

void tensor_add_scalar(tensor t, dtype n);
void tensor_sub_scalar(tensor t, dtype n);
void tensor_mul_scalar(tensor t, dtype n);
void tensor_div_scalar(tensor t, dtype n);
uint8_t tensor_add_inplace(tensor t1, const tensor t2);
uint8_t tensor_sub_inplace(tensor t1, const tensor t2);
tensor tensor_add(const tensor t1, const tensor t2);
tensor tensor_sub(const tensor t1, const tensor t2);

void tensor_map(tensor t, dtype (*func)(dtype));
void tensor_print(const tensor t);

#endif

