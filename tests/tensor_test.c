#include "tensor_test.h"

void tensor_test_is_empty(void) 
{
	/* Depends on tensor_init_zero */
	uint32_t s[4] = {2, 5, 3, 7};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_zero(t2, s, 4);

    tensor_assert(tensor_is_empty(t1), "(empty tensor not detected)");
    tensor_assert(!tensor_is_empty(t2), "(non empty tensor not detected)");

	tensor_destroy(t1);
	tensor_destroy(t2);
}

void tensor_test_is_equal(void)
{
	/* Depends on tensor_cpy, tensor_is_equal, tensor_init_zero, tensor_init_rand */
	uint32_t s[4] = {2, 5, 3, 7};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor_init_zero(t1, s, 4);
	tensor_init_one(t2, s, 4);
	tensor_assert_ne(t1, t2);

	tensor_init_rand(t1, s, 4, (dtype) 30);
	tensor_cpy(t2, t1);

	tensor_assert_eq(t1, t2);

	tensor_destroy(t1);
	tensor_destroy(t2);
}

void tensor_test_check_size(void)
{
    uint32_t size[] = {3, 2, 5, 0};
    tensor_assert(_tensor_check_size(size, 3), "(valid size declared as invalid)");
    tensor_assert(!_tensor_check_size(size, 5), "(no dimension should be 0)");
    tensor_assert(_tensor_check_size(size, 0), "(rank can be 0)");
    tensor_assert(!_tensor_check_size(size, -3), "(rank should be non negative)");
}

void tensor_test_set_size(void)
{
    uint32_t size[] = {3, 2, 7};
	tensor t = tensor_new();

    tensor_assert(_tensor_set_size(t, size, 3), "(size should be set without error)");
    tensor_assert(t->num_elem == 3 * 2 * 7, "(wrong number of elements)");

	tensor_destroy(t);
}

void tensor_test_set(void)
{
	/* Depends on tensor_is_equal, tensor_init_zero, tensor_init_rand */
	uint32_t s[4] = {2, 5, 3, 7};
	uint32_t index[4] = {0, 0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_rand(t1, s, 4, (dtype) 30);
	tensor_init_zero(t2, s, 4);

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

void tensor_test_get(void)
{
	/* Depends on tensor_is_equal, tensor_set, tensor_init_zero, tensor_init_rand */
	bool status;
	uint32_t s[4] = {2, 5, 3, 7};
	uint32_t index[4] = {0, 0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_rand(t1, s, 4, (dtype) 30);
	tensor_init_zero(t2, s, 4);

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

void tensor_test_init_one(void)
{
	/* Depends on tensor_is_equal, tensor_set, tensor_init_rand */
	uint32_t s[3] = {2, 5, 7};
	uint32_t index[3] = {0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_rand(t1, s, 3, (dtype) 30);
	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_set(t1, index, 1);
			}
		}
	}

	tensor_assert(tensor_init_one(t2, s, 3), "(there should be no error when initing)");
    tensor_assert_eq(t1, t2);

	tensor_destroy(t1);
	tensor_destroy(t2);
}

void tensor_test_init_zero(void)
{
	/* Depends on tensor_is_equal, tensor_set, tensor_init_rand */
	uint32_t s[3] = {2, 5, 7};
	uint32_t index[3] = {0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_rand(t1, s, 3, (dtype) 30);
	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_set(t1, index, 0);
			}
		}
	}

	tensor_assert(tensor_init_zero(t2, s, 3), "(there should be no error when initing)");
    tensor_assert_eq(t1, t2);

	tensor_destroy(t1);
	tensor_destroy(t2);
}

void tensor_test_init_rand(void)
{
	/* Depends on tensor_is_equal, tensor_set, tensor_init_rand */
	uint32_t s[3] = {2, 5, 7};
	uint32_t index[3] = {0, 0, 0};
	tensor t1 = tensor_new();

	tensor_assert(tensor_init_rand(t1, s, 3, (dtype) 30), "(there should be no error when initing)");

	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_assert(tensor_set(t1, index, 0), "mute");
			}
		}
	}

	tensor_destroy(t1);
}

void tensor_test_cpy(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_init_zero */
	uint32_t s[3] = {2, 5, 7};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_zero(t2, s, 3);

    tensor_assert(tensor_cpy(t1, t2), "(there should be no error when copying)");
    tensor_assert_eq(t1, t2);

	tensor_destroy(t1);
	tensor_destroy(t2);
}
