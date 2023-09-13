#include "tensoriter.h"

tensoriter_scalar tensoriter_scalar_create(tensor t)
{
    /* Creates an iterator over the values of a tensor. If two tensors have the
     * same size the iterator will always iterate over them in the same order.
     *
     * @param t The tensor to iterate over
     *
     * @return The iterator, NULL in case of an error
     */
	assert(!tensor_is_empty(t));

	tensoriter_scalar it = malloc(sizeof(struct _tensor_scalar_iterator));
	if (it == NULL) return NULL;

	it->t = t;
	it->index = calloc(sizeof(uint32_t), t->rank);

	return it;
}

void tensoriter_scalar_destroy(tensoriter_scalar it)
{
    /* Destroys an iterator.
     *
     * @param it The iterator to destroy
     */
	free(it->index);
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
    bool end = true;

    for (uint8_t i = 0; i < it->t->rank; i++) {
        if (it->index[i] < it->t->size[i] - 1) {
            (it->index[i])++;
            end = false;
            break;
        } else {
            it->index[i] = 0;
        }
    }

	if (end) {
		tensoriter_scalar_destroy(it);
		return false;
	}

	return true;
}

dtype tensoriter_scalar_get(tensoriter_scalar it, bool *success)
{
    /* Gets the current value of the iterator.
     *
     * @param it The iterator to operate on
     * @param success Is set if not NULL and defines whether the get operation
     *      was successful
     *
     * @return The current value of the iterator
     */
	return tensor_get(it->t, it->index, success);
}

bool tensoriter_scalar_set(tensoriter_scalar it, dtype value)
{
    /* Sets the value of the tensor which the iterator is pointing to at the
     * moment.
     *
     * @param it The iterator to operate on
     * @param value The value to insert
     *
     */
	return tensor_set(it->t, it->index, value);
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
		dtype x = tensoriter_scalar_get(it, NULL);
		tensoriter_scalar_set(it, func(x));
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
        dtype x = tensoriter_scalar_get(it, NULL);
		tensoriter_scalar_set(it, DTYPE_ADD(x, scalar));
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
        dtype x = tensoriter_scalar_get(it, NULL);
		tensoriter_scalar_set(it, DTYPE_SUB(x, scalar));
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
        dtype x = tensoriter_scalar_get(it, NULL);
		tensoriter_scalar_set(it, DTYPE_MUL(x, scalar));
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
        dtype x = tensoriter_scalar_get(it, NULL);
		tensoriter_scalar_set(it, DTYPE_DIV(x, scalar));
	} while(tensoriter_scalar_next(it));
}

