#include "tensorfunc_test.h"

void tensor_test_fill(void)
{
    // TODO
}

void tensor_test_inspect(void) 
{
    // TODO
}

void tensor_test_map(void)
{
    // TODO
}

dtype tensor_test_map_helper(dtype d) {
    static uint32_t contained = 0;
    if(((1 << ((uint32_t) d - 1)) & contained) == 0) {
        contained |= 1 << ((uint32_t) d - 1);
        return DTYPE_ZERO;
    } else {
        return d;
    }
}

void tensor_test_map_inplace(void)
{
    /* Depends on tensor_init_one, tensor_init_zero, tensor_set*/
	uint32_t s[3] = {2, 4, 4};
	uint32_t index[3] = {0, 0, 0};
	tensor t = tensor_new();
	tensor t0 = tensor_new();

	tensor_init_zero(t0, s, 3);

	tensor_init_one(t, s, 3);
    float i = 1;
	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_set(t, index, i++);
			}
		}
	}
    
    tensor_map_inplace(t, &tensor_test_map_helper);

    tensor_assert_eq(t0, t);

    tensor_destroy(t);
}

void tensor_test_combine(void) 
{
    // TODO
}

void tensor_test_combine_inplace(void)
{
    // TODO
}

void tensor_test_add_scalar(void)
{
    /* Depends on tensor_init_one, tensor_add_inplace */
	uint32_t s[4] = {2, 5, 3, 7};

	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

	tensor_init_one(t1, s, 4);
	tensor_init_one(t2, s, 4);
	tensor_init_one(t3, s, 4);

    tensor_add_inplace(t1, t2);
    tensor_add_inplace(t1, t2);
    tensor_add_inplace(t1, t2);

    tensor_add_scalar(t3, 3.0);

    tensor_assert_eq(t1, t3);

    tensor_destroy(t1);
    tensor_destroy(t2);
    tensor_destroy(t3);
}

void tensor_test_sub_scalar(void)
{
    /* Depends on tensor_init_one, tensor_add_inplace */
	uint32_t s[4] = {2, 5, 3, 7};

	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

	tensor_init_one(t1, s, 4);
	tensor_init_one(t2, s, 4);
	tensor_init_one(t3, s, 4);

    tensor_add_inplace(t1, t2);
    tensor_add_inplace(t1, t2);
    tensor_add_inplace(t1, t2);

    tensor_sub_scalar(t1, 3.0);

    tensor_assert_eq(t1, t3);

    tensor_destroy(t1);
    tensor_destroy(t2);
    tensor_destroy(t3);
}

void tensor_test_mul_scalar(void)
{
    /* Depends on tensor_init_one, tensor_init_zero */
	uint32_t s[4] = {2, 5, 3, 7};

	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_one(t1, s, 4);
	tensor_init_zero(t2, s, 4);

    tensor_mul_scalar(t1, 0.0);

    tensor_assert_eq(t1, t2);

    tensor_destroy(t1);
    tensor_destroy(t2);
}

void tensor_test_div_scalar(void)
{
    /* Depends on tensor_init_one, tensor_add_inplace */
	uint32_t s[4] = {2, 5, 3, 7};

	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

	tensor_init_one(t1, s, 4);
	tensor_init_one(t2, s, 4);
	tensor_init_one(t3, s, 4);

    tensor_add_inplace(t1, t2);
    tensor_add_inplace(t1, t2);
    tensor_add_inplace(t1, t2);

    tensor_div_scalar(t3, 4.0);

    tensor_assert_eq(t1, t3);

    tensor_destroy(t1);
    tensor_destroy(t2);
    tensor_destroy(t3);
}

void tensor_test_add_inplace(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_set */
	uint32_t s[3] = {3, 2, 4};
	uint32_t index[3] = {0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_one(t2, s, 3);
    tensor_init_one(t3, s, 3);

	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_assert(tensor_set(t1, index, index[0] + index[1] + index[2]), "mute");
				tensor_assert(tensor_set(t2, index, (s[0] + s[1] + s[2]) - (index[0] + index[1] + index[2])), "mute");
                tensor_assert(tensor_set(t3, index, (s[0] + s[1] + s[2])), "mute");
			}
		}
	}

    tensor_add_inplace(t1, t2);
    tensor_assert_eq(t1, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
}

void tensor_test_sub_inplace(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_init_zero */
	uint32_t s[3] = {3, 2, 4};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_one(t2, s, 3);
    tensor_init_zero(t3, s, 3);

    tensor_sub_inplace(t1, t2);
    tensor_assert_eq(t1, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
}

void tensor_test_mul_inplace(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_init_zero */
	uint32_t s[3] = {3, 2, 4};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

    tensor_init_rand(t1, s, 3, (dtype) 30);
    tensor_init_zero(t2, s, 3);

    tensor_mul_inplace(t1, t2);
    tensor_assert_eq(t1, t2);

	tensor_destroy(t1);
	tensor_destroy(t2);
}

void tensor_test_div_inplace(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_init_zero, tensor_add_inplace */
	uint32_t s[3] = {3, 2, 4};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_one(t2, s, 3);
    tensor_init_one(t3, s, 3);

    tensor_add_inplace(t1, t3);
    tensor_add_inplace(t1, t3);
    tensor_add_inplace(t2, t3);
    tensor_add_inplace(t2, t3);

    tensor_div_inplace(t1, t2);
    tensor_assert_eq(t1, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
}

void tensor_test_add(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_set */
	uint32_t s[3] = {3, 2, 4};
	uint32_t index[3] = {0, 0, 0};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_one(t2, s, 3);
    tensor_init_one(t3, s, 3);

	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_assert(tensor_set(t1, index, index[0] + index[1] + index[2]), "mute");
				tensor_assert(tensor_set(t2, index, (s[0] + s[1] + s[2]) - (index[0] + index[1] + index[2])), "mute");
                tensor_assert(tensor_set(t3, index, (s[0] + s[1] + s[2])), "mute");
			}
		}
	}

    tensor t4 = tensor_add(t1, t2);
    tensor_assert_eq(t4, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
	tensor_destroy(t4);
}

void tensor_test_sub(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_init_zero */
	uint32_t s[3] = {3, 2, 4};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_one(t2, s, 3);
    tensor_init_zero(t3, s, 3);

    tensor t4 = tensor_sub(t1, t2);
    tensor_assert_eq(t4, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
	tensor_destroy(t4);
}

void tensor_test_mul(void)
{
    /* Depends on tensor_is_equal, tensor_init_rand, tensor_init_zero */
	uint32_t s[3] = {3, 2, 4};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_rand(t1, s, 3, (dtype) 100);
    tensor_init_zero(t2, s, 3);
    tensor_init_zero(t3, s, 3);

    tensor t4 = tensor_mul(t1, t2);
    tensor_assert_eq(t4, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
	tensor_destroy(t4);
}

void tensor_test_div(void)
{
    /* Depends on tensor_is_equal, tensor_init_one, tensor_init_zero, tensor_add_inplace */
	uint32_t s[3] = {3, 2, 4};
	tensor t1 = tensor_new();
	tensor t2 = tensor_new();
	tensor t3 = tensor_new();

    tensor_init_one(t1, s, 3);
    tensor_init_one(t2, s, 3);
    tensor_init_one(t3, s, 3);

    tensor_add_inplace(t1, t3);
    tensor_add_inplace(t1, t3);
    tensor_add_inplace(t2, t3);
    tensor_add_inplace(t2, t3);

    tensor t4 = tensor_div(t1, t2);
    tensor_assert_eq(t4, t3);

	tensor_destroy(t1);
	tensor_destroy(t2);
	tensor_destroy(t3);
	tensor_destroy(t4);
}
