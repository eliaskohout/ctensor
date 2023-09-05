#include "tensoriter_test.h"

void tensoriter_test_scalar_next(void)
{
    /* Depends on tensor_init_one */
	uint32_t s[4] = {2, 5, 3, 7};
	tensor t = tensor_new();

	tensor_init_one(t, s, 4);
    tensoriter_scalar iter = tensoriter_scalar_create(t);

    uint32_t i = 0;
    do {
        i++;
    } while (tensoriter_scalar_next(iter));

    tensor_assert(i == t->num_elem, "(not the rigth number of values)");

    tensor_destroy(t);
}

void tensoriter_test_scalar_get(void)
{
    /* Depends on tensor_init_one, tensor_set, tensoriter_scalar_next */
	uint32_t s[4] = {2, 4, 4};
	uint32_t index[4] = {0, 0, 0};
	tensor t = tensor_new();

	tensor_init_one(t, s, 3);
    float i = 1;
	for (index[0] = 0; index[0] < s[0]; ++index[0]) {
		for (index[1] = 0; index[1] < s[1]; ++index[1]) {
			for (index[2] = 0; index[2] < s[2]; ++index[2]) {
				tensor_set(t, index, i++);
			}
		}
	}

    uint32_t contained = 0;
    tensoriter_scalar iter = tensoriter_scalar_create(t);
    do {
        uint32_t value = (uint32_t) *tensoriter_scalar_get(iter);
        tensor_assert(((1 << (value - 1)) & contained) == 0, "mute");
        contained |= 1 << (value - 1);
    } while (tensoriter_scalar_next(iter));
    tensor_assert((contained & 0) == 0, "(missed a value)");

    tensor_destroy(t);
}

dtype tensoriter_test_scalar_map_helper(dtype d) {
    static uint32_t contained = 0;
    if(((1 << ((uint32_t) d - 1)) & contained) == 0) {
        contained |= 1 << ((uint32_t) d - 1);
        return DTYPE_ZERO;
    } else {
        return d;
    }
}

void tensoriter_test_scalar_map(void)
{
    /* Depends on tensor_init_one, tensor_init_zero, tensor_set*/
	uint32_t s[4] = {2, 4, 4};
	uint32_t index[4] = {0, 0, 0};
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
    
    tensoriter_scalar iter = tensoriter_scalar_create(t);
    tensoriter_scalar_map(iter, &tensoriter_test_scalar_map_helper);

    tensor_assert_eq(t0, t);

    tensor_destroy(t);
}

void tensoriter_test_scalar_map_add(void)
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

    tensoriter_scalar iter = tensoriter_scalar_create(t3);
    tensoriter_scalar_map_add(iter, 3.0);

    tensor_assert_eq(t1, t3);

    tensor_destroy(t1);
    tensor_destroy(t2);
    tensor_destroy(t3);
}

void tensoriter_test_scalar_map_sub(void)
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

    tensoriter_scalar iter = tensoriter_scalar_create(t1);
    tensoriter_scalar_map_sub(iter, 3.0);

    tensor_assert_eq(t1, t3);

    tensor_destroy(t1);
    tensor_destroy(t2);
    tensor_destroy(t3);
}

void tensoriter_test_scalar_map_mul(void)
{
    /* Depends on tensor_init_one, tensor_init_zero */
	uint32_t s[4] = {2, 5, 3, 7};

	tensor t1 = tensor_new();
	tensor t2 = tensor_new();

	tensor_init_one(t1, s, 4);
	tensor_init_zero(t2, s, 4);

    tensoriter_scalar iter = tensoriter_scalar_create(t1);
    tensoriter_scalar_map_mul(iter, 0.0);

    tensor_assert_eq(t1, t2);

    tensor_destroy(t1);
    tensor_destroy(t2);
}

void tensoriter_test_scalar_map_div(void)
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

    tensoriter_scalar iter = tensoriter_scalar_create(t1);
    tensoriter_scalar_map_div(iter, 4.0);

    tensor_assert_eq(t1, t3);

    tensor_destroy(t1);
    tensor_destroy(t2);
    tensor_destroy(t3);
}
