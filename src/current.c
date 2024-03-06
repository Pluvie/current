/**
 * The whole point of this source file is to take advantage of compiler optimizations,
 * without being constrained to keep al sources into one huge .c file.
 *
 * If the compiler sees all the single .c files as a single entity (this file) it is
 * able to do inlining optimizations. */

#include "current/arena.c"
#include "current/map.c"
#include "current/vector.c"
