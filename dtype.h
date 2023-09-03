#ifndef _DTYPE_H_INCLUDED_
#define _DTYPE_H_INCLUDED_


/* Defining the datatype of the tensor */
typedef float dtype;
/* dtype needs to implement add, sub, mul and div, */
#define DTYPE_ADD(a, b) ((a) + (b))
#define DTYPE_SUB(a, b) ((a) - (b))
#define DTYPE_MUL(a, b) ((a) * (b))
#define DTYPE_DIV(a, b) ((a) / (b))
/* equal and not equal,*/
#define DTYPE_EQ(a, b) ((a) == (b))
#define DTYPE_NE(a, b) ((a) != (b))
/* one and zero, */
#define DTYPE_ONE 1.0
#define DTYPE_ZERO 0.0
/* and a random and pruint8_t function */
#define DTYPE_RAND(max) ((float) rand() / RAND_MAX * (max))
#define DTYPE_PRINT(a) (printf(" %4.1f ", (a)))


#endif // _DTYPE_H_INCLUDED_
