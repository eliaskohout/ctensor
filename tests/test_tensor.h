#ifndef _TEST_TENSOR_H_INCLUDED_
#define _TEST_TENSOR_H_INCLUDED_

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../tensor.h"

#define NUM_TEST_FUNC 14

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

#define tensor_assert(X, msg)   do{ 								                        \
	FILE* stream = stderr; 					 				                                \
	if (!(X)) { 										                                        \
                fputs(ANSI_COLOR_RED "Assertion failed: " ANSI_COLOR_RESET, stream); 		\
		fprintf(stream, 								                                    \
			"function %s, file %s, line %i. ", __func__, __FILE__, __LINE__); 	            \
                fputs((msg), stream); 								                        \
                fputc('\n', stream); 								                        \
        } else if (strcmp((msg), "mute") != 0) { 							                    \
                fputs(ANSI_COLOR_GREEN "Assertion succeeded: " ANSI_COLOR_RESET, stream); 	\
		fprintf(stream, 								                                    \
			"function %s, file %s, line %i. ", __func__, __FILE__, __LINE__); 	            \
                fputc('\n', stream); 								                        \
	} 											                                            \
} while (0)

#define tensor_assert_eq(X, Y)  tensor_assert(tensor_is_equal((X), (Y)), "(tensor_assert_eq)")
#define tensor_assert_ne(X, Y)  tensor_assert(!tensor_is_equal((X), (Y)), "(tensor_assert_ne)")


void test_tensor_run_all(void);

void test_tensor_is_empty(void);
void test_tensor_is_equal(void);
void test_tensor_check_size(void);
void test_tensor_set_size(void);
void test_tensor_set(void);
void test_tensor_get(void);
void test_tensor_init_one(void);
void test_tensor_init_zero(void);
void test_tensor_init_rand(void);
void test_tensor_cpy(void);
void test_tensor_add_inplace(void);
void test_tensor_sub_inplace(void);
void test_tensor_add(void);
void test_tensor_sub(void);

#endif // _TEST_TENSOR_H_INCLUDED_
