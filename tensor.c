#include "tensor.h"

tensor tensor_new(void)
{
    /* Creates a new tensor struct and returns it.
     *
     * @return A tensor (pointer to memory for a _tensor struct)
     */
	return calloc(1, sizeof(struct _tensor));
}

void tensor_destroy(tensor t)
{
    /* Destroys a tensor struct by free its memory.
     *
     * @param t The tensor that should be deleted
     */
	if (!tensor_is_empty(t)) {
		free(t->size);
		free(t->elements);
		free(t->stride);
	}
	free(t);
}

bool tensor_is_empty(const tensor t)
{
    /* Checks whether a tensor is empty.
     *
     * @param t The tensor to check
     *
     * @return true when the tensor is empty, false otherwise
     */
	return t->elements == NULL || t->size == NULL;
}

bool tensor_is_equal(const tensor t1, const tensor t2)
{
    /* Checks whether two tensor are equal.
     *
     * @param t1 The first tensor
     * @param t2 The seconds tensor
     *
     * @return true when the two tensors are equal, false otherwise
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	uint32_t i;
	if (t1->rank != t2->rank) return false;
	for (i = 0; i < t1->rank; i++) {
		if (t1->size[i] != t2->size[i]) return false;
	}
	for (i = 0; i < t1->num_elem; i++) {
		if (DTYPE_NE(t1->elements[i], t2->elements[i])) return false;
	}
	return true;
}

bool _tensor_check_size(const uint32_t *size, uint8_t rank)
{
    /* Checks whether a size array is valid.
     *
     * @param size A size array
     * @param rank The length of the size array
     *
     * @return true when the size is valid, false otherwise
     */
	uint8_t i;
	if(rank < 0) return false;
	for(i = 0; i < rank; i++) {
		if(size[i] < 1) return false;
	}
	return true;
}

bool _tensor_set_size(tensor t, const uint32_t *size, uint8_t rank)
{
	/* Sets the size of a Tensor. During this process all data in the tensor t 
     * is lost.
     *
     * @param t The tensor that should be changed
     * @param size The final size of the tensor t
     * @param rank The length of size
     *
     * @return true if the process was successful, false when an error occured
     */

	uint32_t *temp_size;
	uint32_t *temp_stride;
	dtype *temp_elements;
	uint8_t i;
	uint32_t num_elem = 1;

	if(!_tensor_check_size(size, rank)) return false;

	/* Try allocating memory for the size/ stride array of the tensor */
	for(i = 0; i < rank; i++) {
		num_elem *= size[i];
	}
	temp_size = malloc(rank * sizeof(uint32_t));
	temp_stride = malloc(rank * sizeof(uint32_t));
	temp_elements = malloc(num_elem * sizeof(dtype));
	if((temp_size == NULL && rank != 0) || (temp_stride == NULL && rank != 0) || temp_elements == NULL) {
		free(temp_size);
		free(temp_stride);
		return false;
	}

	/* Freeing old memory. */
	free(t->size);
	free(t->stride);
	free(t->elements);

	/* Setting the size array */
	t->size = temp_size;
	if(rank != 0) memcpy(t->size, size, rank * sizeof(uint32_t));
	t->rank = rank;
	/* Setting the stride array */
	t->stride = temp_stride;
	t->stride[0] = 1;
	for(i = 1; i < t->rank; i++) {
		t->stride[i] = t->stride[i - 1] * t->size[i - 1];
	}
	/* Setting the elements pointer and memory usage */
	t->elements = temp_elements;
	t->num_elem = num_elem;

	return true;
}

bool tensor_set(tensor t, const uint32_t *index, dtype val)
{
    /* Set the value at a index of a tensor.
     *
     * @param t The tensor to change
     * @param index The index of the value that should change, the length of 
     *     this array is defined by the rank of t
     * @param val The updated value
     *
     * @return true if the change was successful, false otherwise
     */
	assert(!tensor_is_empty(t));

	uint8_t i;
	uint32_t offset = 0;

	if(t->rank == 0) {
		t->elements[0] = val;
		return true;
	}

	for(i = 0; i < t->rank; i++) {
		if(t->size[i] <= index[i]) return false;
		offset += t->stride[i] * index[i];
	}

	t->elements[offset] = val;
	return true;
}

dtype tensor_get(const tensor t, const uint32_t *index, bool *success)
{
    /* Gets a value at a index from a tensor.
     * 
     * @param t The tensor from which to get the value from
     * @param index The index of the value to get, the length of this array is 
     *     defined by the rank of t
     * @param success Is set according to the exit status of the function, if it
     *     is NULL it is ignored
     *
     * @return The retrieved value, DTYPE_NULL in case of an error
     */
	assert(!tensor_is_empty(t));

	uint8_t i;
	uint32_t offset = 0;

	if(t->rank == 0) return t->elements[0];

	for(i = 0; i < t->rank; i++) {
		if(t->size[i] <= index[i]) {
			if(success != NULL) *success = false;
			return DTYPE_ZERO;
		}
		offset += t->stride[i] * index[i];
	}

	if(success != NULL) *success = true;
	return t->elements[offset];
}

bool tensor_init_one(tensor t, const uint32_t *size, uint8_t rank)
{
    /* Inits (sets the size) and filles a tensor with ones.
     * 
     * @param t The tensor to fill
     * @param size The final size of the tensor t
     * @param rank The length of size array
     *
     * @return true when successful, false otherwise
     */
	uint32_t i;

	if(!_tensor_set_size(t, size, rank)) return false;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ONE;
	}
	return true;
}

bool tensor_init_zero(tensor t, const uint32_t *size, uint8_t rank)
{
    /* Inits (sets the size) and filles a tensor with zeros.
     * 
     * @param t The tensor to fill
     * @param size The final size of the tensor t
     * @param rank The length of size array
     *
     * @return true when successful, false otherwise
     */
	uint32_t i;

	if(!_tensor_set_size(t, size, rank)) return false;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ZERO;
	}
	return true;
}

bool tensor_init_rand(tensor t, const uint32_t *size, uint8_t rank, dtype max)
{
    /* Inits (sets the size) and filles a tensor with random values below or
     * equal to the max value.
     * 
     * @param t The tensor to fill
     * @param size The final size of the tensor t
     * @param rank The length of size array
     * @param max The maximal value filled in
     *
     * @return true when successful, false otherwise
     */
	uint32_t i;
	static long last_seed;
	last_seed += time(NULL) * 200 + rand();
	srand(last_seed);

	if(!_tensor_set_size(t, size, rank)) return false;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_RAND(max);
	}
	return true;
}

bool tensor_cpy(tensor t1, const tensor t2)
{
    /* Copies the contents of t2 into t1.
     *
     * @param t1 The tensor in which to copy the values
     * @param t2 The tensor from which to copy the values
     *
     * @return true when successful, false otherwise
     */
	assert(!tensor_is_empty(t2));

	uint32_t i;
	if(!_tensor_set_size(t1, t2->size, t2->rank)) return false;
	for(i = 0; i < t2->num_elem; i++) {
		t1->elements[i] = t2->elements[i];
	}
	return true;
}

bool tensor_add_inplace(tensor t1, const tensor t2)
{
    /* Adds the values of t2 onto the values of t1. t1 and t2 need to have the
     * same size.
     *
     * @param t1 The tensor on which the values of t2 are added
     * @param t2 The tensor whose values are added
     *
     * @return true when successful, false otherwise
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	uint32_t i;

	if(t1->rank != t2->rank) return false;
	for(i = 0; i < t1->rank; i++) {
		if(t1->size[i] != t2->size[i]) return false;
	}
	for(i = 0; i < t1->num_elem; i++) {
		t1->elements[i] = DTYPE_ADD(t1->elements[i], t2->elements[i]);
	}
	return true;
}

bool tensor_sub_inplace(tensor t1, const tensor t2)
{
    /* Subtracts the values of t2 from the values of t1. t1 and t2 need to have
     * the same size.
     *
     * @param t1 The tensor from which the values of t2 are subtracted
     * @param t2 The tensor whose values are subtracted
     *
     * @return true when successful, false otherwise
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	uint32_t i;

	if(t1->rank != t2->rank) return false;
	for(i = 0; i < t1->rank; i++) {
		if(t1->size[i] != t2->size[i]) return false;
	}
	for(i = 0; i < t1->num_elem; i++) {
		t1->elements[i] = DTYPE_SUB(t1->elements[i], t2->elements[i]);
	}
	return true;
}

tensor tensor_add(const tensor t1, const tensor t2)
{
    /* Adds to tensors returning the result as a tensor.
     * 
     * @param t1 The first tensor to add
     * @param t2 The second tensor to add
     *
     * @return The result of the operation, NULL if an error occurs
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	tensor t3 = tensor_new();
	if(t3 == NULL) return NULL;
	if (!tensor_cpy(t3, t1)) return NULL;
	if (!tensor_add_inplace(t3, t2)) return NULL;
	return t3;
}

tensor tensor_sub(const tensor t1, const tensor t2)
{
    /* Subtracts to tensors returning the result as a tensor.
     * 
     * @param t1 The tensor to subtract from
     * @param t2 The tensor that is subtracted
     *
     * @return The result of the operation, NULL if an error occurs
     */
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	tensor t3 = tensor_new();
	if(t3 == NULL) return NULL;
	if (!tensor_cpy(t3, t1)) return NULL;
	if (!tensor_sub_inplace(t3, t2)) return NULL;
	return t3;

}

void tensor_print(const tensor t)
{
    /* Prints a tensor to stdout.
     *
     * @param t The tensor to print
     */
	uint32_t i, j;
	uint32_t *index;

	if(tensor_is_empty(t)){
		printf("<empty tensor>\n");
		return;
	}

	printf("Tensor of rank %i and size (", t->rank);
	for(i = 0; i < t->rank - 1; i++) {
		printf("%i, ", t->size[i]);
	}
	if(t->rank == 0) printf("): ");
	else printf("%i): ", t->size[t->rank - 1]);


	if(t->rank == 0) {
	/* scalar */
		DTYPE_PRINT(t->elements[0]);
		putchar('\n');
	} else if (t->rank == 1) {
	/* column vector */
		if(t->size[0] == 1) {
			putchar('(');
			DTYPE_PRINT(t->elements[0]);
			printf(")\n");
		} else {
			printf("\n/");
			DTYPE_PRINT(t->elements[0]);
			printf("\\\n");
			for(i = 1; i < t->size[0] - 1; i++) {
				putchar('|');
				DTYPE_PRINT(t->elements[i]);
				printf("|\n");
			}
			printf("\\");
			DTYPE_PRINT(t->elements[t->size[0] - 1]);
			printf("/\n");
		}
	} else if (t->rank == 2) {
	/* matix */
		index = malloc(sizeof(int) * 2);
		if(t->size[0] == 1) {
			putchar('(');
			index[0] = 0;
			for(i = 0; i < t->size[1]; i++) {
				index[1] = i;
				DTYPE_PRINT(tensor_get(t, index, NULL));
			}
			printf(")\n");
		} else {
			printf("\n/");
			index[0] = 0;
			for(i = 0; i < t->size[1]; i++) {
				index[1] = i;
				DTYPE_PRINT(tensor_get(t, index, NULL));
			}
			printf("\\\n");
			for(i = 1; i < t->size[0] - 1; i++) {
				putchar('|');
				index[0] = i;
				for(j = 0; j < t->size[1]; j++) {
					index[1] = j;
					DTYPE_PRINT(tensor_get(t, index, NULL));
				}
				printf("|\n");
			}
			printf("\\");
			index[0] = t->size[0] - 1;
			for(i = 0; i < t->size[1]; i++) {
				index[1] = i;
				DTYPE_PRINT(tensor_get(t, index, NULL));
			}
			printf("/\n");
		}
		free(index);
	} else {
		putchar('[');
		for(i = 0; i < t->num_elem; i++) {
			DTYPE_PRINT(t->elements[i]);
		}
		putchar(']');
		putchar('\n');
	}
}

