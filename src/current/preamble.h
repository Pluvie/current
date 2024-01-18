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

/**
 * Alias for strings. */
#define string char*

/**
 * Useful general macros. */
#define function(name, type)  type name
#define countof(name)         (sizeof(name) / sizeof(*(name)))
#define lengthof(name)        (countof(name) - 1)
#define next_pow2(number)     (1 << ((8 * sizeof(uint32)) - __builtin_clz(number - 1)))
