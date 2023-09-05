#include "tensoriter.h"

tensoriter_scalar tensoriter_scalar_create(tensor t)
{
    /* Creates an iterator over the values of a tensor.
     *
     * @param t The tensor to iterate over
     *
     * @return The iterator
     */
	assert(!tensor_is_empty(t));

	tensoriter_scalar it = malloc(sizeof(struct _tensor_scalar_iterator));
	if (it == NULL) return NULL;

	it->current = t->elements;
	it->length = t->num_elem;

	return it;
}

void tensoriter_scalar_destroy(tensoriter_scalar it)
{
    /* Destroys an iterator.
     *
     * @param it The iterator to destroy
     */
	free(it);
}

bool tensoriter_scalar_next(tensoriter_scalar it)
{
    /* Checks whether the given iterator has a next value and sets this value 
     * as the current value if available. If there is not next value the 
     * iterator is destroyed and false is returned.
     *
     * @param it The iterator to evaluate
     *
     * @return true if there is a next value, false otherwise
     */
	if (it->length == 1) {
		tensoriter_scalar_destroy(it);
		return false;
	}

	it->current++;
	it->length--;

	return true;
}

dtype *tensoriter_scalar_get(tensoriter_scalar it)
{
    /* Gets the current value of the iterator.
     *
     * @param it The iterator to operate on
     *
     * @return A pointer to the current value
     */
	return it->current;
}

void tensoriter_scalar_map(tensoriter_scalar it, dtype (*func)(dtype))
{
    /* Replaces every value in an iterator with the result of given function
     * with the old value as a parameter.
     *
     * @param it The iterator to operate on
     * @param func The map function that is called
     */
	do {
		dtype *el = tensoriter_scalar_get(it);
		*el = func(*el);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_add(tensoriter_scalar it, dtype scalar)
{
    /* Adds a fixed scalar value to all the values of the iterator.
     *
     * @param it The iterator to operate on
     * @param scalar The value to add
     */
	do {
        dtype* x = tensoriter_scalar_get(it);
		*x = DTYPE_ADD(*x, scalar);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_sub(tensoriter_scalar it, dtype scalar)
{
    /* Subtracts a fixed scalar value from all the values of the iterator.
     *
     * @param it The iterator to operate on
     * @param scalar The value to subtract
     */
	do {
        dtype* x = tensoriter_scalar_get(it);
		*x = DTYPE_SUB(*x, scalar);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_mul(tensoriter_scalar it, dtype scalar)
{
    /* Multiplies a fixed scalar value with all the values of the iterator.
     *
     * @param it The iterator to operate on
     * @param scalar The value to multiply
     */
	do {
        dtype* x = tensoriter_scalar_get(it);
		*x = DTYPE_MUL(*x, scalar);
	} while(tensoriter_scalar_next(it));
}

void tensoriter_scalar_map_div(tensoriter_scalar it, dtype scalar)
{
    /* Divides all the values of the iterator by a fixed scalar value.
     *
     * @param it The iterator to operate on
     * @param scalar The value to divide by
     */
	do {
        dtype* x = tensoriter_scalar_get(it);
		*x = DTYPE_DIV(*x, scalar);
	} while(tensoriter_scalar_next(it));
}

