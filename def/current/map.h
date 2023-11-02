/**
 * Main map data, held just before the map pointer.
 * It contains all the metadata needed for the map to operate.
 *
 * This will be referenced by the macro #map_data, which will move the map pointer
 * behind by `sizeof(struct __map_data) + sizeof(T)` bytes, where `T` is the map
 * value type.
 *
 * This technique is called "Fat Pointer", [see more here](
 * https://libcello.org/learn/a-fat-pointer-library). */
struct __map_data {
  uint32  length;
  uint32  capacity;
  uint32  key_size;
  uint32  value_size;
  void*   keys;
  bool*   usage;
  uint32* hashes;
  uint32  (*hash)(void*);
  bool    (*compare)(void*, void*);
  struct {
    int32   pos;
    uint32  hash;
    uint32  offset;
  } find;
};

/**
 * Minimum map capacity. */
#define MAP_MIN_CAPACITY 8

/**
 * Macro to refer map data types. */
#define map(key_type, value_type)                                                       \
  value_type*

/**
 * Returns the size of the vector metadata struct. */
#define map_datasize                                                                    \
  (sizeof(struct __map_data))

/**
 * Returns the vector metadata struct pointer from a vector pointer. */
#define map_data(map_ptr)                                                               \
  (struct __map_data*) (map_ptr - 1) - 1

/**
 * Returns the vector capacity. */
#define map_capacity(map_ptr)                                                           \
  ((map_data(map_ptr))->capacity)

/**
 * Returns the vector length. */
#define map_length(map_ptr)                                                             \
  ((map_data(map_ptr))->length)

/**
 * Computes the map hash for the given key. */
#define map_hash(map_ptr, key)                                                          \
  ((map_data(map_ptr))->hash(key))

/**
 * Computes the map load factor. */
#define map_load(map_ptr, amount)                                                       \
  ((dec64) (map_length(map_ptr) + amount) / (dec64) map_capacity(map_ptr))

/**
 * Calculates the map minimum capacity value given a capacity number. */
#define map_min_cap(capacity)                                                           \
  (capacity < MAP_MIN_CAPACITY ? MAP_MIN_CAPACITY : next_pow2(capacity))

/**
 * Allocates a new vector of the provided `key_type` and `value_type`. The initial
 * capacity shall be equal to #MAP_MIN_CAPACITY. */
#define map_new(key_type, value_type)                                                   \
  (map_new_cap(key_type, value_type, MAP_MIN_CAPACITY))

/**
 * Allocates a new vector using the provided `key_type`, `value_type`
 * and `initial_capacity`. */
#define map_new_cap(key_type, value_type, initial_capacity) (                           \
  strcmp(#key_type, "char*") == 0 ?                                                     \
    __map_new(                                                                          \
        map_min_cap(initial_capacity),                                                  \
        sizeof(key_type),                                                               \
        sizeof(value_type),                                                             \
        __map_string_key_hash,                                                          \
        __map_string_key_compare) :                                                     \
    __map_new(                                                                          \
        map_min_cap(initial_capacity),                                                  \
        sizeof(key_type),                                                               \
        sizeof(value_type),                                                             \
        NULL,                                                                           \
        NULL))                                                                          \

/**
 * Returns `true` if the map has the given key, `false` otherwise. */
#define map_has(map_ptr, key)                                                           \
  (map_find(map_data(map_ptr), key) > 0)

/**
 * Returns the map value associated to the given key. If the key is not present,
 * then the __zero value__ of the map value type is returned. */
#define map_get(map_ptr, key) (                                                         \
  __map_find(map_data(map_ptr), key, map_hash(map_ptr, key), true),                     \
  *(map_ptr + ((map_data(map_ptr))->find.pos)))

/**
 * Sets the value for the given key in the map. If the key is already present,
 * the value will be overwritten. */
#define map_set(map_ptr, key, value) (                                                  \
  map_check_rehash(map_ptr, 1) ?                                                        \
  __map_find(map_data(map_ptr), key, map_hash(map_ptr, key), false),                    \
  __map_use(map_data(map_ptr), key),                                                    \
  ((*(map_ptr + (map_data(map_ptr))->find.offset) = value), 1) : 0)

/**
 * Deletes the value for the given key in the map. */
#define map_delete(map_ptr, key) (                                                      \
  __map_find(map_data(map_ptr), key, map_hash(map_ptr, key), true),                     \
  __map_delete(map_data(map_ptr), key), 1)

/**
 * Checks if the map needs a rehash. */
#define map_check_rehash(map_ptr, amount) (                                             \
  (map_load(map_ptr, amount) >= 0.7) ? map_rehash(map_ptr) : 1)

/**
 * Rehashes the whole map. This process will allocate more space for all the map
 * memory regions, and every key of the map will undergo a repositioning process. */
#define map_rehash(map_ptr)                                                             \
  (map_ptr = __map_rehash(map_ptr, map_data(map_ptr)), 1)

/**
 * Releases all memory regions used by the map. */
#define map_free(map_ptr)                                                               \
  (__map_free(map_data(map_ptr)))

/**
 * Map functions. */
function(__map_delete, void) (struct __map_data* data, void* key);
function(__map_find, int32) (struct __map_data* data, void* key, uint32 hash, bool presence);
function(__map_free, void) (struct __map_data* data);
function(__map_new, void*) (uint32 initial_capacity, uint32 key_size, uint32 value_size, uint32 (*hash_function)(void*), bool (*compare_function)(void*, void*));
function(__map_rehash, void*) (void* map_ptr, struct __map_data* data);
function(__map_string_key_compare, bool) (void* s1, void* s2);
function(__map_string_key_hash, uint32) (void* key);
function(__map_use, void) (struct __map_data* data, void* key);

#include "map/print.h"
