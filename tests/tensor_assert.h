#ifndef _TENSOR_ASSERT_H_INCLUDED_
#define _TENSOR_ASSERT_H_INCLUDED_


#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

#define tensor_assert(X, msg)   do{ 								                        \
	FILE* stream = stderr; 					 				                                \
	if (!(X)) { 										                                    \
                fputs(ANSI_COLOR_RED "Assertion failed: " ANSI_COLOR_RESET, stream); 		\
		fprintf(stream, 								                                    \
			"function %s, file %s, line %i. ", __func__, __FILE__, __LINE__); 	            \
                fputs((msg), stream); 								                        \
                fputc('\n', stream); 								                        \
        } else if (strcmp((msg), "mute") != 0) { 							                \
                fputs(ANSI_COLOR_GREEN "Assertion succeeded: " ANSI_COLOR_RESET, stream); 	\
		fprintf(stream, 								                                    \
			"function %s, file %s, line %i. ", __func__, __FILE__, __LINE__); 	            \
                fputc('\n', stream); 								                        \
	} 											                                            \
} while (0)

#define tensor_assert_eq(X, Y)  tensor_assert(tensor_is_equal((X), (Y)), "(tensor_assert_eq)")
#define tensor_assert_ne(X, Y)  tensor_assert(!tensor_is_equal((X), (Y)), "(tensor_assert_ne)")


#endif // _TENSOR_ASSERT_H_INCLUDED_
