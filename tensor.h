#ifndef TENSOR_H_INCLUDED
#define TENSOR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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
/* and a random and print function */
#define DTYPE_RAND(max) ((float) rand() / RAND_MAX * (max))
#define DTYPE_PRINT(a) (printf(" %4.1f ", (a)))


typedef struct _tensor {
	dtype *elements;
	int dimension;
	int *size;
	int *index_offsets;
	int num_elem;
} *tensor;


tensor tensor_new(void);
void tensor_destroy(tensor t);

int tensor_is_empty(const tensor t);
int tensor_is_equal(const tensor t1, const tensor t2);

int _tensor_check_size(const int *size, int dim);
int _tensor_set_size(tensor t, const int *size, int dim);

int tensor_set(tensor t, const int *index, dtype val);
dtype tensor_get(const tensor t, const int *index, int *success);

int tensor_init_one(tensor t, int dimension, const int *size);
int tensor_init_zero(tensor t, int dimension, const int *size);
int tensor_init_rand(tensor t, int dimension, const int *size, dtype max);
int tensor_cpy(tensor t1, const tensor t2);

void tensor_add_scalar(tensor t, dtype n);
void tensor_sub_scalar(tensor t, dtype n);
void tensor_mult_scalar(tensor t, dtype n);
void tensor_div_scalar(tensor t, dtype n);
int tensor_add(tensor t1, const tensor t2);
int tensor_sub(tensor t1, const tensor t2);

void tensor_for_each_elem(tensor t, dtype (*func)(dtype));
void tensor_print(const tensor t);

#endif

