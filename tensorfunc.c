#include "tensorfunc.h"

void tensor_fill(tensor t, dtype (*func)(void))
{
    /* Filles a tensor with the values provided by a function.
     *
     * @param t The tensor to fill
     * @param func The function providing the values, it is expected to have
     *      no sidel effects.
     */
	assert(!tensor_is_empty(t));
    // TODO
}

void tensor_inspect(const tensor t, void (*func)(dtype))
{
    /* Goes over every element in a tensor and calls a function on it.
     *
     * @param t The tensor that provides the values
     * @param func The function that is called with the values
     */
	assert(!tensor_is_empty(t));
    // TODO
}

tensor tensor_map(const tensor t, dtype (*func)(dtype))
{
    /* Creates a new tensor in which the result of the given function
     * with the values of the given tensor as parameters is stored.
     *
     * @param t The tensor that provides the values
     * @param func The map function that is called, it is expected to have no
     *      side effects
     *
     * @return The newly created tensor
     */
	assert(!tensor_is_empty(t));
    // TODO
}

void tensor_map_inplace(tensor t, dtype (*func)(dtype))
{
    /* Replaces every value in a tensor with the result of the given function
     * with the old value as a parameter.
     *
     * @param t The tensor to operate on
     * @param func The map function that is called, it is expected to have no 
     *      side effects
     */
	assert(!tensor_is_empty(t));
    // TODO
}

tensor tensor_combine(const tensor t1, const tensor t2, dtype (*func)(dtype, dtype))
{
    /* Combines every value of two tensors and stores the result in a third
     * tensor. t1 and t2 need to have the same shape.
     *
     * @param t1 The first tensor
     * @param t2 The second tensor
     * @param func The function that takes in the values of t1 and t2 and
     *      returns the result that is stored in the created tensor, it is
     *      expected to have no side effects
     *
     * @return The tensor with the result of the combination of t1 and t2
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));
    // TODO
}

void tensor_combine_inplace(tensor t1, const tensor t2, dtype (*func)(dtype, dtype))
{
    /* Combines every value of two tensor and stores the result in the first of
     * the tensors. t1 and t2 need to have the same shape.
     *
     * @param t1 The tensor in which to store the result
     * @param t2 The second tensor of the operation
     * @param func The function that takes in the values of t1 and t2 and
     *      returns the result that is stored in t1, it is expected to have
     *      no side effects
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));
    // TODO

}

void tensor_add_scalar(tensor t, dtype scalar)
{
    /* Adds a fixed scalar value to all the values of a tensor.
     *
     * @param t The tensor to operate on
     * @param scalar The value to add
     */
    // TODO
}

void tensor_sub_scalar(tensor t, dtype scalar)
{
    /* Subtracts a fixed scalar value from all the values of a tensor.
     *
     * @param t The tensor to operate on
     * @param scalar The value to subtract
     */
    // TODO
}

void tensor_mul_scalar(tensor t, dtype scalar)
{
    /* Multiplies a fixed scalar value with all the values of a tensor.
     *
     * @param t The tensor to operate on
     * @param scalar The value to multiply
     */
    // TODO
}

void tensor_div_scalar(tensor t, dtype scalar)
{
    /* Divides all the values of a tensor by a fixed scalar value.
     *
     * @param t The tensor to operate on
     * @param scalar The value to divide by
     */
    // TODO
}

void tensor_add_inplace(tensor t1, const tensor t2)
{
    /* Adds the values of t2 onto the values of t1. t1 and t2 need to have the
     * same shape.
     *
     * @param t1 The tensor on which the values of t2 are added
     * @param t2 The tensor whose values are added
     */
    // TODO
}

void tensor_sub_inplace(tensor t1, const tensor t2)
{
    /* Subtracts the values of t2 from the values of t1. t1 and t2 need to have
     * the same shape.
     *
     * @param t1 The tensor from which the values of t2 are subtracted
     * @param t2 The tensor whose values are subtracted
     */
    // TODO
}

void tensor_mul_inplace(tensor t1, const tensor t2)
{
    /* Multiplies the values of t2 onto t1 element wise. t1 and t2 need to 
     * have the same shape.
     * 
     * @param t1 The tensor to multiply onto
     * @param t2 The tensor to multiply with
     */
    // TODO
}

void tensor_div_inplace(tensor t1, const tensor t2)
{
    /* Divides the values of t2 by the values of t1 element wise. t1 and t2 
     * need to have the same shape.
     * 
     * @param t1 The tensor to devide
     * @param t2 The tensor to devide by
     */
    // TODO
}

tensor tensor_add(const tensor t1, const tensor t2)
{
    /* Adds two tensors returning the result as a tensor. t1 and t2 need to
     * have the same shape.
     * 
     * @param t1 The first tensor to add
     * @param t2 The second tensor to add
     *
     * @return The result of the operation, NULL if an error occurs
     */
    // TODO
}

tensor tensor_sub(const tensor t1, const tensor t2)
{
    /* Subtracts two tensors returning the result as a tensor. t1 and t2 need
     * to have the same shape.
     * 
     * @param t1 The tensor to subtract from
     * @param t2 The tensor that is subtracted
     *
     * @return The result of the operation, NULL if an error occurs
     */
    // TODO
}

tensor tensor_mul(const tensor t1, const tensor t2)
{
    /* Multiplies two tensors element wise returning the result as a tensor.
     * t1 and t2 need to have the same shape.
     * 
     * @param t1 The first tensor to multipy
     * @param t2 The second tensor to multipy
     *
     * @return The result of the operation, NULL if an error occurs
     */
    // TODO
}

tensor tensor_div(const tensor t1, const tensor t2)
{
    /* Divides two tensors element wise returning the result as a tensor. t1 
     * and t2 need to have the same shape.
     * 
     * @param t1 The dividend
     * @param t2 The divisor
     *
     * @return The result of the operation, NULL if an error occurs
     */
    // TODO
}
