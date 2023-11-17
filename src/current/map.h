/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/

/**
 * Defines the map configuration options. */
struct __map_config {
  uint64  initial_capacity;
  uint64  key_size;
  uint64  value_size;
  uint64  (*hash)(void*);
  bool    (*compare)(void*, void*);
  bool    copy_keys;
  uint64  key_size_copy;
  uint64  (*key_size_func)(void*);
  void    (*key_copy_func)(void*, void*, uint64);
  bool    copy_values;
  uint64  value_size_copy;
  uint64  (*value_size_func)(void*);
  void    (*value_copy_func)(void*, void*, uint64);
  struct arena* arena;
};

/**
 * Main map data, held just before the map pointer.
 * It contains all the metadata needed for the map to operate.
 *
 * This will be referenced by the macro #map_fp, which will move the map pointer
 * behind by `sizeof(struct __map_fp) + sizeof(T)` bytes, where `T` is the map
 * value type.
 *
 * This technique is called "Fat Pointer", [see more here](
 * https://libcello.org/learn/a-fat-pointer-library). */
struct __map_fp {
  uint64  length;
  uint64  capacity;
  void*   keys;
  bool*   usage;
  uint64* hashes;
  struct __map_config config;
};

/**
 * Defines the result output of the function #__map_find. */
enum __map_find_output {
  __Map_Find_Default  = 0,
  __Map_Find_Offset   = 1,
};

/**
 * Defines the operation mode of the function #__map_use. */
enum __map_use_opmode {
  __Map_Use_Default   = 0,
  __Map_Use_Rehashing = 1,
};

/**
 * Map function declarations. */

function(__map_delete, void) (struct __map_fp*, void*, uint64);
function(__map_find, int64) (struct __map_fp*, void*, uint64, enum __map_find_output);
function(__map_free, void) (struct __map_fp*);
function(__map_new, void*) (struct __map_config);
function(__map_rehash, void*) (void*, struct __map_fp*);
function(__map_use, int64) (struct __map_fp*, void*, uint64, enum __map_use_opmode);

function(__map_prebuilt_int32_compare, bool) (void*, void*);
function(__map_prebuilt_int32_hash, uint64) (void*);
function(__map_prebuilt_int32_print, void) (int32);
function(__map_prebuilt_int64_compare, bool) (void*, void*);
function(__map_prebuilt_int64_hash, uint64) (void*);
function(__map_prebuilt_int64_print, void) (int64);
function(__map_prebuilt_string_hash, uint64) (void*);
function(__map_prebuilt_string_print, void) (char*);
function(__map_prebuilt_string_compare, bool) (void*, void*);
function(__map_prebuilt_string_length, uint64) (void*);

/**
 * Minimum map capacity. */
#define MAP_MIN_CAPACITY 8

/**
 * Defines the `map` type. */
#define map(key_type, value_type)                                                       \
  value_type*

/**
 * Returns the map fat pointer from a map pointer. */
#define map_fp(map_ptr)                                                                 \
  (struct __map_fp*) (map_ptr - 1) - 1

/**
 * Creates a new map, with the given *name*, *key_type* and *value_type*.
 * Extra configuration options may be passed using the macro variadic args. */
#define map_new(name, key_type, value_type, ...)                                        \
  map(key_type, value_type) name;                                                       \
  {                                                                                     \
    struct __map_config config = {                                                      \
      .key_size = sizeof(key_type),                                                     \
      .value_size = sizeof(value_type),                                                 \
      ##__VA_ARGS__ };                                                                  \
    name = __map_new(config);                                                           \
  }

/**
 * Returns the vector capacity. */
#define map_capacity(map_ptr)                                                           \
  ((map_fp(map_ptr))->capacity)

/**
 * Returns the vector length. */
#define map_length(map_ptr)                                                             \
  ((map_fp(map_ptr))->length)

/**
 * Computes the map load factor. */
#define map_load(map_ptr, amount)                                                       \
  ((dec64) (map_length(map_ptr) + amount) / (dec64) map_capacity(map_ptr))

/**
 * Computes the map hash for the given key. */
#define map_hash(map_ptr, key)                                                          \
  ((map_fp(map_ptr))->config.hash(key))

/**
 * Returns `true` if the map has the given key, `false` otherwise. */
#define map_has(map_ptr, key)                                                           \
  (map_find(map_fp(map_ptr), key)) > 0)

/**
 * Retrieves the key at the given index using the given type. */
#define map_key(map_ptr, type, index)                                                   \
  ((type*) (map_fp(map_ptr))->keys)[index]

/**
 * Determines if the given index is used in the map. */
#define map_used(map_ptr, index)                                                        \
  ((map_fp(map_ptr))->usage)[index]

/**
 * Finds a key in the map. */
#define map_find(map_ptr, key, presence)                                                \
  __map_find(map_fp(map_ptr), key, map_hash(map_ptr, key), presence)

/**
 * Sets as used a key in the map. */
#define map_use(map_ptr, key, rehashing)                                                \
  __map_use(map_fp(map_ptr), key, map_hash(map_ptr, key), rehashing)

/**
 * Returns the map value associated to the given key. If the key is not present,
 * then the __zero value__ of the map value type is returned. */
#define map_get(map_ptr, key)                                                           \
  (*(map_ptr + (map_find(map_ptr, key, __Map_Find_Default))))

/**
 * Sets the value for the given key in the map. If the key is already present,
 * the value will be overwritten. */
#define map_set_dbg(map_ptr, key, value) (                                                  \
  map_load(map_ptr, 1) >= 0.7                                                           \
    ? ((map_ptr = __map_rehash(map_ptr, map_fp(map_ptr))),                              \
      (*(map_ptr + (map_use(map_ptr, key, __Map_Use_Default))) = value),                \
      value)                                                                            \
    : ((*(map_ptr + (map_use(map_ptr, key, __Map_Use_Default))) = value),               \
      value))

#define map_set(map_ptr, key, value) (                                                  \
  map_load(map_ptr, 1) >= 0.7                                                           \
    ? map_use(map_ptr, key, __Map_Use_Default)                                                                            \
    : map_use(map_ptr, key, __Map_Use_Default))

/**
 * Deletes the value for the given key in the map. */
#define map_delete(map_ptr, key)                                                        \
  __map_delete(map_fp(map_ptr), key, map_hash(map_ptr, key))

/**
 * Releases all memory regions used by the map. */
#define map_free(map_ptr)                                                               \
  (__map_free(map_fp(map_ptr)))

/**
 * Loops through all the used indexes of the map. */
#define map_each(map_ptr, key_type, value_type, iter_name)                              \
  for (struct { key_type key; value_type value; uint64 counter; uint64 index; }         \
      iter_name = { .counter = 0, .index = 0 };                                         \
      iter_name.counter < map_capacity(map_ptr); iter_name.counter++)                   \
    if (iter_name.index++,                                                              \
        iter_name.key = map_key(map_ptr, key_type, iter_name.counter),                  \
        iter_name.value = map_ptr[iter_name.counter],                                   \
        !(map_used(map_ptr, iter_name.counter))) { iter_name.index--; continue; } else

/**
 * Loops through all the indexes of the map, both used and not used. */
#define map_all(map_ptr, key_type, value_type, iter_name)                               \
  for (struct { key_type key; value_type value; bool used; uint64 hash; uint64 index; } \
      iter_name =  { .index = 0 };                                                      \
      iter_name.index < map_capacity(map_ptr); iter_name.index++)                       \
    if (iter_name.key = map_key(map_ptr, key_type, iter_name.index),                    \
        iter_name.value = map_ptr[iter_name.index],                                     \
        iter_name.hash = (map_fp(map_ptr))->hashes[iter_name.index],                    \
        iter_name.used = map_used(map_ptr, iter_name.index), true)

#define map_print(map_ptr, key_type, key_printer, value_type, value_printer)            \
  fprintf(stderr, "\n----\nMap: %p\n----\n", map_ptr);                                  \
  map_all(map_ptr, key_type, value_type, iter) {                                        \
    fprintf(stderr, "[%4li] ", iter.index);                                             \
    fprintf(stderr, "[%32li] ", iter.hash);                                             \
    iter.used ? fprintf(stderr, "[■] ") : fprintf(stderr, "[ ] ");                      \
    fprintf(stderr, "["); key_printer(iter.key); fprintf(stderr, "] ");                 \
    fprintf(stderr, "["); value_printer(iter.value); fprintf(stderr, "]\n");            \
  }
