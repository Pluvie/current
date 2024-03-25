/**
 * The whole point of this source file is to take advantage of compiler optimizations,
 * without being constrained to keep al sources into one huge .c file.
 *
 * If the compiler sees all the single .c files as a single entity (this file) it is
 * able to do inlining optimizations. */

#include "./vector/create.c"
#include "./vector/destroy.c"
#include "./vector/from_data.c"
#include "./vector/get.c"
#include "./vector/pop.c"
#include "./vector/pretty_print.c"
#include "./vector/push.c"
#include "./vector/resize.c"
#include "./vector/set.c"
