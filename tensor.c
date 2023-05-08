#include "tensor.h"

tensor tensor_new(void)
{
	return calloc(1, sizeof(struct _tensor));
}

void tensor_destroy(tensor t)
{
	if (!tensor_is_empty(t)) {
		free(t->size);
		free(t->elements);
		free(t->index_offsets);
	}
	free(t);
}

bool tensor_is_empty(const tensor t)
{
	return t->elements == NULL || t->size == NULL;
}

bool tensor_is_equal(const tensor t1, const tensor t2)
{
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

uint8_t _tensor_check_size(const uint32_t *size, uint8_t rank)
{
	uint8_t i;
	if(rank < 0) return 0;
	for(i = 0; i < rank; i++) {
		if(size[i] < 1) return 0;
	}
	return 1;
}

uint8_t _tensor_set_size(tensor t, const uint32_t *size, uint8_t rank)
{
	/* Sets the size of a Tensor. During this process all data in the tensor t is lost. */

	uint32_t *temp_size;
	uint32_t *temp_index_offset;
	dtype *temp_elements;
	uint8_t i, j;
	uint32_t num_elem = 1;

	if(!_tensor_check_size(size, rank)) return 0;

	/* Try allocating memory for the size/ index_offset array of the tensor */
	for(i = 0; i < rank; i++) {
		num_elem *= size[i];
	}
	temp_size = malloc(rank * sizeof(uint32_t));
	temp_index_offset = malloc(rank * sizeof(uint32_t));
	temp_elements = malloc(num_elem * sizeof(dtype));
	if((temp_size == NULL && rank != 0) || (temp_index_offset == NULL && rank != 0) || temp_elements == NULL) {
		free(temp_size);
		free(temp_index_offset);
		return 0;
	}

	/* Freeing old memory. */
	free(t->size);
	free(t->index_offsets);
	free(t->elements);

	/* Setting the size array */
	t->size = temp_size;
	if(rank != 0) memcpy(t->size, size, rank * sizeof(uint32_t));
	t->rank = rank;
	/* Setting the index_offset array */
	t->index_offsets = temp_index_offset;
	for(i = 0; i < t->rank; i++) {
		t->index_offsets[i] = 1;
		for(j = i + 1; j < t->rank; j++) {
			t->index_offsets[i] *= t->size[j];
		}
	}
	/* Setting the elements pointer and memory usage */
	t->elements = temp_elements;
	t->num_elem = num_elem;

	return 1;
}

uint8_t tensor_set(tensor t, const uint32_t *index, dtype val)
{
	assert(!tensor_is_empty(t));

	uint8_t i;
	uint32_t offset = 0;

	if(t->rank == 0) {
		t->elements[0] = val;
		return 1;
	}

	for(i = 0; i < t->rank; i++) {
		if(t->size[i] <= index[i]) return 0;
		offset += t->index_offsets[i] * index[i];
	}

	t->elements[offset] = val;
	return 1;
}

dtype tensor_get(const tensor t, const uint32_t *index, uint8_t *success)
{
	assert(!tensor_is_empty(t));

	uint8_t i;
	uint32_t offset = 0;

	if(t->rank == 0) return t->elements[0];

	for(i = 0; i < t->rank; i++) {
		if(t->size[i] <= index[i]) {
			if(success != NULL) *success = 0;
			return 0;
		}
		offset += t->index_offsets[i] * index[i];
	}

	if(success != NULL) *success = 1;
	return t->elements[offset];
}

uint8_t tensor_init_one(tensor t, uint8_t rank, const uint32_t *size)
{
	uint32_t i;

	if(!_tensor_set_size(t, size, rank)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ONE;
	}
	return 1;
}

uint8_t tensor_init_zero(tensor t, uint8_t rank, const uint32_t *size)
{
	uint32_t i;

	if(!_tensor_set_size(t, size, rank)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ZERO;
	}
	return 1;
}

uint8_t tensor_init_rand(tensor t, uint8_t rank, const uint32_t *size, dtype max)
{
	uint32_t i;
	static long last_seed;
	last_seed += time(NULL) * 200 + rand();
	srand(last_seed);

	if(!_tensor_set_size(t, size, rank)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_RAND(max);
	}
	return 1;
}

uint8_t tensor_cpy(tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t2));

	uint32_t i;
	if(!_tensor_set_size(t1, t2->size, t2->rank)) return 0;
	for(i = 0; i < t2->num_elem; i++) {
		t1->elements[i] = t2->elements[i];
	}
	return 1;
}

uint8_t tensor_add_inplace(tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	uint32_t i;
	if(t1->rank != t2->rank) return 0;
	for(i = 0; i < t1->rank; i++) {
		if(t1->size[i] != t2->size[i]) return 0;
	}
	for(i = 0; i < t1->num_elem; i++) {
		t1->elements[i] = DTYPE_ADD(t1->elements[i], t2->elements[i]);
	}
	return 1;
}

uint8_t tensor_sub_inplace(tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	uint32_t i;
	if(t1->rank != t2->rank) return 0;
	for(i = 0; i < t1->rank; i++) {
		if(t1->size[i] != t2->size[i]) return 0;
	}
	for(i = 0; i < t1->num_elem; i++) {
		t1->elements[i] = DTYPE_SUB(t1->elements[i], t2->elements[i]);
	}
	return 1;
}

tensor tensor_add(const tensor t1, const tensor t2)
{
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
	uint32_t i, j;
	uint32_t *indx;

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
		indx = malloc(sizeof(int) * 2);
		if(t->size[0] == 1) {
			putchar('(');
			indx[0] = 0;
			for(i = 0; i < t->size[1]; i++) {
				indx[1] = i;
				DTYPE_PRINT(tensor_get(t, indx, NULL));
			}
			printf(")\n");
		} else {
			printf("\n/");
			indx[0] = 0;
			for(i = 0; i < t->size[1]; i++) {
				indx[1] = i;
				DTYPE_PRINT(tensor_get(t, indx, NULL));
			}
			printf("\\\n");
			for(i = 1; i < t->size[0] - 1; i++) {
				putchar('|');
				indx[0] = i;
				for(j = 0; j < t->size[1]; j++) {
					indx[1] = j;
					DTYPE_PRINT(tensor_get(t, indx, NULL));
				}
				printf("|\n");
			}
			printf("\\");
			indx[0] = t->size[0] - 1;
			for(i = 0; i < t->size[1]; i++) {
				indx[1] = i;
				DTYPE_PRINT(tensor_get(t, indx, NULL));
			}
			printf("/\n");
		}
		free(indx);
	} else {
		putchar('[');
		for(i = 0; i < t->num_elem; i++) {
			DTYPE_PRINT(t->elements[i]);
		}
		putchar(']');
		putchar('\n');
	}
}

