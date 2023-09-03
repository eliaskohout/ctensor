#ifndef _TENSORITERATOR_H_
#define _TENSORITERATOR_H_

#include "tensor.h"

typedef struct _tensor_scalar_iterator {
	dtype *current;
	uint32_t length;
} * tensoriter_scalar;

tensoriter_scalar tensoriter_scalar_create(tensor t);
void tensoriter_scalar_destroy(tensoriter_scalar it);

bool tensoriter_scalar_next(tensoriter_scalar it);
dtype *tensoriter_scalar_get(tensoriter_scalar it);

void tensoriter_scalar_map(tensoriter_scalar it, dtype (*func)(dtype));
void tensoriter_scalar_map_add(tensoriter_scalar it, dtype scalar);
void tensoriter_scalar_map_sub(tensoriter_scalar it, dtype scalar);
void tensoriter_scalar_map_mul(tensoriter_scalar it, dtype scalar);
void tensoriter_scalar_map_div(tensoriter_scalar it, dtype scalar);

#endif // _TENSORITERATOR_H_

