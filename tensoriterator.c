#include "tensoriterator.h"

tensoriter_scalar tensoriter_scalar_create(tensor t)
{
	assert(!tensor_is_empty(t));

	tensoriter_scalar it = malloc(sizeof(struct _tensor_scalar_iterator));
	if (it == NULL) return NULL;

	it->current = t->elements;
	it->length = t->num_elem;

	return it;
}

void tensoriter_scalar_destroy(tensoriter_scalar it)
{
	free(it);
}

uint8_t tensoriter_scalar_next(tensoriter_scalar it)
{
	if (it->length == 1) {
		tensoriter_scalar_destroy(it);
		return 0;
	}

	it->current++;
	it->length--;

	return 1;
}

dtype *tensoriter_scalar_get(tensoriter_scalar it)
{
	return it->current;
}

void tensoriter_scalar_map(tensoriter_scalar it, dtype (*func)(dtype))
{
	do {
		dtype *el = tensoriter_scalar_get(it);
		*el = func(*el);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_add(tensoriter_scalar it, dtype scalar)
{
	do {
		DTYPE_ADD(*tensoriter_scalar_get(it), scalar);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_sub(tensoriter_scalar it, dtype scalar)
{
	do {
		DTYPE_SUB(*tensoriter_scalar_get(it), scalar);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_mul(tensoriter_scalar it, dtype scalar)
{
	do {
		DTYPE_MUL(*tensoriter_scalar_get(it), scalar);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_div(tensoriter_scalar it, dtype scalar)
{
	do {
		DTYPE_DIV(*tensoriter_scalar_get(it), scalar);
	} while(tensoriter_scalar_next(it));
}

