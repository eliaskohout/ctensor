#ifndef _TENSORFUNC_H_
#define _TENSORFUNC_H_

#include "tensor.h"

void tensor_fill(tensor t, dtype (*func)(void));
void tensor_inspect(const tensor t, void (*func)(dtype));

tensor tensor_map(const tensor t, dtype (*func)(dtype));
void tensor_map_inplace(tensor t, dtype (*func)(dtype));

tensor tensor_combine(const tensor t1, const tensor t2, dtype (*func)(dtype, dtype));
bool tensor_combine_inplace(tensor t1, const tensor t2, dtype (*func)(dtype, dtype));

void tensor_add_scalar(tensor t, dtype scalar);
void tensor_sub_scalar(tensor t, dtype scalar);
void tensor_mul_scalar(tensor t, dtype scalar);
void tensor_div_scalar(tensor t, dtype scalar);

bool tensor_add_inplace(tensor t1, const tensor t2);
bool tensor_sub_inplace(tensor t1, const tensor t2);
bool tensor_mul_inplace(tensor t1, const tensor t2);
bool tensor_div_inplace(tensor t1, const tensor t2);

tensor tensor_add(const tensor t1, const tensor t2);
tensor tensor_sub(const tensor t1, const tensor t2);
tensor tensor_mul(const tensor t1, const tensor t2);
tensor tensor_div(const tensor t1, const tensor t2);

#endif // _TENSORFUNC_H_
