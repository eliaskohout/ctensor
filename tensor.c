#include "tensor.h"
#include <stdio.h>
#include <stdlib.h>

tensor tensor_new(void)
{
	return calloc(1, sizeof(struct _tensor));
}

void tensor_destroy(tensor t)
{
	if (!tensor_is_empty(t)) {
		free(t->size);
		free(t->elements);
	}
}

int tensor_is_empty(const tensor t){
	return t->elements == NULL || t->size == NULL;
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
	int *temp;
	dtype *t_temp;
	int i, num_elem = 1;

	for(i = 0; i < dim; i++) {
		num_elem *= size[i];
	}

	if(!_tensor_check_size(size, dim)) return 0;
	/* Try allocating memory for the size array of the Tensor */
	temp = realloc(t->size, dim * sizeof(int));
	if(temp == NULL && dim != 0) return 0;
	/* Try allocating memory for the Tensor */
	t_temp = realloc(t->elements, num_elem * sizeof(dtype));
	if(t_temp == NULL) {
		/* Revert to before the function call and return */
		t->size = realloc(temp, t->dimension * sizeof(int));
		if(t->size == NULL && t->dimension != 0) {
			printf("Fatal error in _tensor_set_size when reallocating memory.");
			exit(-1);
		}
		return 0;
	}

	/* Setting the size array */
	t->size = temp;
	if(dim != 0) memcpy(t->size, size, dim * sizeof(int));
	t->dimension = dim;
	/* Setting the elements pointer and memory usage */
	t->elements = t_temp;
	t->num_elem = num_elem;

	return 1;
}

int tensor_set(tensor t, const int *index, dtype val)
{
	int i, offset = 0;
	if(tensor_is_empty(t)) return 0;
	if(t->dimension == 0) return t->elements[0] = val;

	for(i = 0; i < t->dimension - 1; i++) {
		if(t->size[i] <= index[i]) return 0;
		offset += t->size[i + 1] * index[i];
	}
	if(t->size[t->dimension - 1] <= index[t->dimension - 1]) return 0;
	offset += index[t->dimension - 1];
	t->elements[offset] = val;
	return 1;
}

dtype tensor_get(const tensor t, const int *index, int *success)
{
	int i, offset = 0;
	if(tensor_is_empty(t)) return 0;
	if(t->dimension == 0) return t->elements[0];

	for(i = 0; i < t->dimension - 1; i++) {
		if(t->size[i] <= index[i]) {
			if(success != NULL) *success = 0;
			return 0;
		}
		offset += t->size[i + 1] * index[i];
	}
	if(t->size[t->dimension - 1] <= index[t->dimension - 1]) {
		if(success != NULL) *success = 0;
		return 0;
	}
	offset += index[t->dimension - 1];

	if(success != NULL) *success = 1;
	return t->elements[offset];
}

int tensor_init_one(tensor t, int dimension, const int *size)
{
	int i;

	if(!_tensor_set_size(t, size, dimension)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = (dtype) 1;
	}
	return 1;
}

int tensor_init_zero(tensor t, int dimension, const int *size)
{
	int i;

	if(!_tensor_set_size(t, size, dimension)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = (dtype) 0;
	}
	return 1;
}

int tensor_init_rand(tensor t, int dimension, const int *size, int max)
{
	int i;
	srand(time(NULL));

	if(!_tensor_set_size(t, size, dimension)) return 0;
	for(i = 0; i < t->num_elem; i++) {
		t->elements[i] = (dtype) (rand() % max);
	}
	return 1;
}

void tensor_for_each_elem(tensor t, dtype (*func)(dtype))
{
	int i;
	srand(time(NULL));

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
	/* Skalar */
		printf(PRINT_STRING, t->elements[0]);
		putchar('\n');
	} else if (t->dimension == 1) {
	/* Spaltenvektor */
		if(t->size[0] == 1) {
			putchar('(');
			printf(PRINT_STRING, t->elements[0]);
			printf(")\n");
		} else {
			printf("\n/");
			printf(PRINT_STRING, t->elements[0]);
			printf("\\\n");
			for(i = 1; i < t->size[0] - 1; i++) {
				putchar('|');
				printf(PRINT_STRING, t->elements[i]);
				printf("|\n");
			}
			printf("\\");
			printf(PRINT_STRING, t->elements[t->size[0] - 1]);
			printf("/\n");
		}
	} else if (t->dimension == 2) {
	/* Matix */
		indx = malloc(sizeof(int) * 2);
		if(t->size[0] == 1) {
			putchar('(');
			indx[0] = 0;
			for(i = 0; i < t->size[1]; i++) {
				indx[1] = i;
				printf(PRINT_STRING, tensor_get(t, indx, NULL));
			}
			printf(")\n");
		} else {
			printf("\n/");
			indx[0] = 0;
			for(i = 0; i < t->size[1]; i++) {
				indx[1] = i;
				printf(PRINT_STRING, tensor_get(t, indx, NULL));
			}
			printf("\\\n");
			for(i = 1; i < t->size[0] - 1; i++) {
				putchar('|');
				indx[0] = i;
				for(j = 0; j < t->size[1]; j++) {
					indx[1] = j;
					printf(PRINT_STRING, tensor_get(t, indx, NULL));
				}
				printf("|\n");
			}
			printf("\\");
			indx[0] = t->size[0] - 1;
			for(i = 0; i < t->size[1]; i++) {
				indx[1] = i;
				printf(PRINT_STRING, tensor_get(t, indx, NULL));
			}
			printf("/\n");
		}
		free(indx);
	} else {
		printf(" print function not yet implemented for dim > 2.");
	}
}

