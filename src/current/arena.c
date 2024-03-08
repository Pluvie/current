/**
 * The whole point of this source file is to take advantage of compiler optimizations,
 * without being constrained to keep al sources into one huge .c file.
 *
 * If the compiler sees all the single .c files as a single entity (this file) it is
 * able to do inlining optimizations. */

#include "./arena/create.c"
#include "./arena/calloc.c"
#include "./arena/destroy.c"
#include "./arena/malloc.c"
#include "./arena/prealloc.c"
#include "./arena/realloc.c"
#include "./arena/region/create.c"
#include "./arena/region/next.c"
#include "./arena/region/search.c"
