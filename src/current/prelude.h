#ifndef CURRENT_TYPES_H
#define CURRENT_TYPES_H

/**
 * Type definitions. */
typedef uint8_t       u8;
typedef uint16_t      u16;
typedef uint32_t      u32;
typedef uint64_t      u64;
typedef int8_t        i8;
typedef int16_t       i16;
typedef int32_t       i32;
typedef int64_t       i64;
typedef float         d32;
typedef double        d64;
typedef long double   d128;
typedef uintptr_t     uptr;
typedef unsigned char byte;
typedef ptrdiff_t     size;
typedef size_t        usize;

#endif


#ifndef CURRENT_MACROS_H
#define CURRENT_MACROS_H

/**
 * Useful general macros. */
#define function(name, type)  type name
#define countof(name)         (sizeof(name) / sizeof(*(name)))
#define lengthof(name)        (countof(name) - 1)
#define log2(number)          (number > 1 ? 64 - __builtin_clzl((u64) number - 1) : 0)
#define next_pow2(number)     (1 << log2(number))
#define is_pow2(number)       (number > 0 ? (number & (number - 1)) == 0 : false)

#endif
