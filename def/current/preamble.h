typedef unsigned char   byte;
typedef int8_t          int8;
typedef int16_t         int16;
typedef int32_t         int32;
typedef int64_t         int64;
typedef uint8_t         uint8;
typedef uint16_t        uint16;
typedef uint32_t        uint32;
typedef uint64_t        uint64;
typedef double          dec;
typedef float           dec32;
typedef double          dec64;
typedef long double     dec128;

#define function(name, type) type name
#define next_pow2(number) (1 << ((8 * sizeof(uint32)) - __builtin_clz(number - 1)))
