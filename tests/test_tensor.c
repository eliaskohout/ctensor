#include "test_tensor.h"
#include <stdint.h>

void test_run_all(void)
{
	int i;
	void (*test_func[NUM_TEST_FUNC])(void) = {
		&test_tensor_is_equal,
		&test_tensor_set,
		&test_tensor_get,
	};

	printf("\n### Running tests... ###\n\n");
	for(i = 0; i < NUM_TEST_FUNC; i++) {
		test_func[i]();
	}
	printf("\n### %i functions tested. ###\n\n", NUM_TEST_FUNC);
}

void test_tensor_is_equal(void)
{
	/* Depends on tensor_cpy, tensor_is_equal, tensor_init_zero, tensor_init_rand */
	uint32_t s[4] = {2, 5, 3, 7};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_zero(t1, 4, s);
	tensor_init_one(t2, 4, s);
	tensor_assert_ne(t1, t2);

	tensor_init_rand(t1, 4, s, 30);
	tensor_cpy(t2, t1);

	tensor_assert_eq(t1, t2);
	tensor_destroy(t1);
	tensor_destroy(t2);
}

void test_tensor_set(void)
{
	/* Depends on tensor_is_equal, tensor_init_zero, tensor_init_rand */
	uint32_t s[4] = {2, 5, 3, 7};
	uint32_t index[4] = {0, 0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_rand(t1, 4, s, 30);
	tensor_init_zero(t2, 4, s);

	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				for (index[3] = 0; index[3] < s[3]; ++index[3]) {
					tensor_assert(tensor_set(t1, index, 0), "mute");
				}
			}
		}
	}
	tensor_assert_eq(t1, t2);
	tensor_destroy(t1);
	tensor_destroy(t2);
}

void test_tensor_get(void)
{
	/* Depends on tensor_is_equal, tensor_set, tensor_init_zero, tensor_init_rand */
	uint8_t status;
	uint32_t s[4] = {2, 5, 3, 7};
	uint32_t index[4] = {0, 0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_rand(t1, 4, s, 30);
	tensor_init_zero(t2, 4, s);

	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				for (index[3] = 0; index[3] < s[3]; ++index[3]) {
					tensor_set(t2, index, tensor_get(t1, index, &status));
					tensor_assert(status, "mute");
				}
			}
		}
	}
	tensor_assert_eq(t1, t2);
	tensor_destroy(t1);
	tensor_destroy(t2);
}

