#include "tensor.h"
#include <stdio.h>

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

int tensor_is_empty(const tensor t)
{
	return t->elements == NULL || t->size == NULL;
}

int tensor_is_equal(const tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	int i;
	if (t1->dimension != t2->dimension) return 0;
	for (i = 0; i < t1->dimension; i++) {
		if (t1->size[i] != t2->size[i]) return 0;
	}
	for (i = 0; i < t1->num_elem; i++) {
		if (DTYPE_NE(t1->elements[i], t2->elements[i])) return 0;
	}
	return 1;
}

int _tensor_check_size(const int *size, int dim)
{
	int i;
	if(dim < 0) return 0;
	for(i = 0; i < dim; i++) {
		if(size[i] < 1) return 0;
	}
	return 1;
}

int _tensor_set_size(tensor t, const int *size, int dim)
{
	/* Sets the size of a Tensor. During this process all data in the tensor t is lost. */

	int *temp1;
	int *temp2;
	dtype *temp3;
	int i, j, num_elem = 1;

	if(!_tensor_check_size(size, dim)) return 0;

	/* Try allocating memory for the size/ index_offset array of the tensor */
	for(i = 0; i < dim; i++) {
		num_elem *= size[i];
	}
	temp1 = malloc(dim * sizeof(int));
	temp2 = malloc(dim * sizeof(int));
	temp3 = malloc(num_elem * sizeof(dtype));
	if((temp1 == NULL && dim != 0) || (temp2 == NULL && dim != 0) || temp3 == NULL) {
		free(temp1);
		free(temp2);
		return 0;
	}

	/* Freeing old memory. */
	free(t->size);
	free(t->index_offsets);
	free(t->elements);

	/* Setting the size array */
	t->size = temp1;
	if(dim != 0) memcpy(t->size, size, dim * sizeof(int));
	t->dimension = dim;
	/* Setting the index_offset array */
	t->index_offsets = temp2;
	for(i = 0; i < t->dimension; i++) {
		t->index_offsets[i] = 1;
		for(j = i + 1; j < t->dimension; j++) {
			t->index_offsets[i] *= t->size[j];
		}
	}
	/* Setting the elements pointer and memory usage */
	t->elements = temp3;
	t->num_elem = num_elem;

	return 1;
}

int tensor_set(tensor t, const int *index, dtype val)
{
	assert(!tensor_is_empty(t));

	int i, offset = 0;

	if(t->dimension == 0) {
		t->elements[0] = val;
		return 1;
	}

	for(i = 0; i < t->dimension; i++) {
		if(t->size[i] <= index[i]) return 0;
		offset += t->index_offsets[i] * index[i];
	}

	t->elements[offset] = val;
	return 1;
}

dtype tensor_get(const tensor t, const int *index, int *success)
{
	assert(!tensor_is_empty(t));

	int i, offset = 0;

	if(t->dimension == 0) return t->elements[0];

	for(i = 0; i < t->dimension; i++) {
		if(t->size[i] <= index[i]) {
			if(success != NULL) *success = 0;
			return 0;
		}
		offset += t->index_offsets[i] * index[i];
	}

	if(success != NULL) *success = 1;
	return t->elements[offset];
}

int tensor_init_one(tensor t, int dimension, const int *size)
{
	int i;

	if(!_tensor_set_size(t, size, dimension)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ONE;
	}
	return 1;
}

int tensor_init_zero(tensor t, int dimension, const int *size)
{
	int i;

	if(!_tensor_set_size(t, size, dimension)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ZERO;
	}
	return 1;
}

int tensor_init_rand(tensor t, int dimension, const int *size, dtype max)
{
	int i;
	static int last_seed;
	last_seed += time(NULL) * 200 + rand();
	srand(last_seed);

	if(!_tensor_set_size(t, size, dimension)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_RAND(max);
	}
	return 1;
}

int tensor_cpy(tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t2));

	int i;
	if(!_tensor_set_size(t1, t2->size, t2->dimension)) return 0;
	for(i = 0; i < t2->num_elem; i++) {
		t1->elements[i] = t2->elements[i];
	}
	return 1;
}

void tensor_add_scalar(tensor t, dtype n)
{
	assert(!tensor_is_empty(t));

	int i;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_ADD(t->elements[i], n);
	}
}

void tensor_sub_scalar(tensor t, dtype n)
{
	assert(!tensor_is_empty(t));

	int i;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_SUB(t->elements[i], n);
	}
}

void tensor_mult_scalar(tensor t, dtype n)
{
	assert(!tensor_is_empty(t));

	int i;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_MUL(t->elements[i], n);
	}
}

void tensor_div_scalar(tensor t, dtype n)
{
	assert(!tensor_is_empty(t));

	int i;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = DTYPE_DIV(t->elements[i], n);
	}
}

int tensor_add_inplace(tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	int i;
	if(t1->dimension != t2->dimension) return 0;
	for(i = 0; i < t1->dimension; i++) {
		if(t1->size[i] != t2->size[i]) return 0;
	}
	for(i = 0; i < t1->num_elem; i++) {
		t1->elements[i] = DTYPE_ADD(t1->elements[i], t2->elements[i]);
	}
	return 1;
}

int tensor_sub_inplace(tensor t1, const tensor t2)
{
	assert(!tensor_is_empty(t1));
	assert(!tensor_is_empty(t2));

	int i;
	if(t1->dimension != t2->dimension) return 0;
	for(i = 0; i < t1->dimension; i++) {
		if(t1->size[i] != t2->size[i]) return 0;
	}
	for(i = 0; i < t1->num_elem; i++) {
		t1->elements[i] = DTYPE_SUB(t1->elements[i], t2->elements[i]);
	}
	return 1;
}

void tensor_map(tensor t, dtype (*func)(dtype))
{
	assert(!tensor_is_empty(t));

	int i;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = func(t->elements[i]);
	}
}

void tensor_print(const tensor t)
{
	int i, j;
	int *indx;

	if(tensor_is_empty(t)){
		printf("<empty tensor>\n");
		return;
	}

	printf("Tensor of dimension %i and size (", t->dimension);
	for(i = 0; i < t->dimension - 1; i++) {
		printf("%i, ", t->size[i]);
	}
	if(t->dimension == 0) printf("): ");
	else printf("%i): ", t->size[t->dimension - 1]);


	if(t->dimension == 0) {
	/* scalar */
		DTYPE_PRINT(t->elements[0]);
		putchar('\n');
	} else if (t->dimension == 1) {
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
	} else if (t->dimension == 2) {
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

