/**
 * The whole point of this source file is to take advantage of compiler optimizations,
 * without being constrained to keep al sources into one huge .c file.
 *
 * If the compiler sees all the single .c files as a single entity (this file) it is
 * able to do inlining optimizations. */

#include "./map/create.c"
#include "./map/del.c"
#include "./map/destroy.c"
#include "./map/entry/add.c"
#include "./map/entry/destroy.c"
#include "./map/entry/get.c"
#include "./map/entry/set.c"
#include "./map/generic/capped_hash.c"
#include "./map/generic/compare.c"
#include "./map/generic/hash.c"
#include "./map/get.c"
#include "./map/has.c"
#include "./map/pretty_print.c"
#include "./map/pretty_print/entry.c"
#include "./map/rehash.c"
#include "./map/set.c"
