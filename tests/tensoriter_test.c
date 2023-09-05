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
        uint32_t x = 1;
        uint32_t value = (uint32_t) *tensoriter_scalar_get(iter);
        tensor_assert(((x << (value - 1)) & contained) == 0, "mute");
        contained |= (x << (value - 1));
    } while (tensoriter_scalar_next(iter));
    tensor_assert((contained & 0) == 0, "(missed a value)");
}

void tensoriter_test_scalar_map(void)
{
    //TODO
}

void tensoriter_test_scalar_map_add(void)
{
    //TODO
}

void tensoriter_test_scalar_map_sub(void)
{
    //TODO
}

void tensoriter_test_scalar_map_mul(void)
{
    //TODO
}

void tensoriter_test_scalar_map_div(void)
{
    //TODO
}
