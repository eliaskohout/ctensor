#ifndef TENSOR_H_INCLUDED
#define TENSOR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PRINT_STRING " %4.1f "

typedef float dtype;

typedef struct _tensor {
	dtype *elements;
	int dimension;
	int *size;
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
int tensor_init_rand(tensor t, int dimension, const int *size, int max);

int tensor_add(tensor t1, const tensor t2);

void tensor_for_each_elem(tensor t, dtype (*func)(dtype));
int tensor_cpy(tensor t1, const tensor t2);
void tensor_print(const tensor t);

#endif

