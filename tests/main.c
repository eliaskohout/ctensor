#include "main.h"

int main(void)
{
	tensor_test_run_all();
	tensoriter_test_run_all();
	return 0;
}

void tensor_test_run_all(void)
{
	int i;
	void (*test_func[NUM_TENSOR_TEST_FUNC])(void) = {
		&tensor_test_is_empty,
		&tensor_test_is_equal,
        &tensor_test_check_size,
        &tensor_test_set_size,
		&tensor_test_set,
		&tensor_test_get,
        &tensor_test_init_one,
        &tensor_test_init_zero,
        &tensor_test_init_rand,
        &tensor_test_cpy,
        &tensor_test_add_inplace,
        &tensor_test_sub_inplace,
        &tensor_test_mul_inplace,
        &tensor_test_div_inplace,
        &tensor_test_add,
        &tensor_test_sub,
        &tensor_test_mul,
        &tensor_test_div,
	};

	printf("\n### Running tests for tensor.c ... ###\n\n");
	for(i = 0; i < NUM_TENSOR_TEST_FUNC; i++) {
		test_func[i]();
	}
	printf("\n### %i functions tested. ###\n\n", NUM_TENSOR_TEST_FUNC);
}

void tensoriter_test_run_all(void)
{
	int i;
	void (*test_func[NUM_TENSORITER_TEST_FUNC])(void) = {
        &tensoriter_test_scalar_next,
        &tensoriter_test_scalar_get,
        &tensoriter_test_scalar_set,
        &tensoriter_test_scalar_map,
        &tensoriter_test_scalar_map_add,
        &tensoriter_test_scalar_map_sub,
        &tensoriter_test_scalar_map_mul,
        &tensoriter_test_scalar_map_div,
	};

	printf("\n### Running tests for tensoriter.c ... ###\n\n");
	for(i = 0; i < NUM_TENSORITER_TEST_FUNC; i++) {
		test_func[i]();
	}
	printf("\n### %i functions tested. ###\n\n", NUM_TENSORITER_TEST_FUNC);
}
