/**
                          .___  ___.      ___      .______   
                          |   \/   |     /   \     |   _  \  
                          |  \  /  |    /  ^  \    |  |_)  | 
                          |  |\/|  |   /  /_\  \   |   ___/  
                          |  |  |  |  /  _____  \  |  |      
                          |__|  |__| /__/     \__\ | _|      
                                                                                      **/

/**
 * Main map data, held just before the map pointer.
 * It contains all the metadata needed for the map to operate.
 *
 * This will be referenced by the macro #map_data, which will move the map pointer
 * behind by `sizeof(struct __map_fp) + sizeof(T)` bytes, where `T` is the map
 * value type.
 *
 * This technique is called "Fat Pointer", [see more here](
 * https://libcello.org/learn/a-fat-pointer-library). */
struct __map_fp {
  arena*  allocator;
  uint64  length;
  uint64  capacity;
  uint64  key_size;
  uint64  value_size;
  void*   keys;
  bool*   usage;
  uint64* hashes;
  uint64  (*hash)(void*);
  bool    (*compare)(void*, void*);
  bool    copy_keys;
  void    (*key_copy)(void*, void*, uint64);
  uint64  (*key_length)(void*);
};

/**
 * Defines the operations of the function #__map_find. */
enum __map_find_op {
  __Map_Find_Default  = 0,
  __Map_Find_Pos      = 1,
  __Map_Find_Offset   = 2,
};

/**
 * Defines the operations of the function #__map_use. */
enum __map_use_op {
  __Map_Use_Default   = 0,
  __Map_Use_Rehashing = 1,
};


function(__map_delete, void) (struct __map_fp*, void*, uint64);
function(__map_find, int64) (struct __map_fp*, void*, uint64, enum __map_find_op);
function(__map_free, void) (struct __map_fp*);
function(__map_new, void*) (int64, arena*, int64, int64);
function(__map_rehash, void*) (void*, struct __map_fp*);
function(__map_use, int64) (struct __map_fp*, void*, uint64, enum __map_use_op);

function(__map_prebuilt_int32_compare, bool) (void*, void*);
function(__map_prebuilt_int32_hash, uint64) (void*);
function(__map_prebuilt_int32_print, void) (int32);
function(__map_prebuilt_int64_compare, bool) (void*, void*);
function(__map_prebuilt_int64_hash, uint64) (void*);
function(__map_prebuilt_int64_print, void) (int64);
function(__map_prebuilt_string_hash, uint64) (void*);
function(__map_prebuilt_string_print, void) (char*);
function(__map_prebuilt_string_compare, bool) (void*, void*);
function(__map_prebuilt_string_copy, void) (void*, void*, uint64);
function(__map_prebuilt_string_length, uint64) (void*);
/**
 * Minimum map capacity. */
#define MAP_MIN_CAPACITY 8

/**
 * Macro to refer map data types. */
#define map(key_type, value_type)                                                       \
  value_type*

/**
 * Returns the size of the vector metadata struct. */
#define map_fp_size                                                                     \
  (sizeof(struct __map_fp))

/**
 * Returns the vector metadata struct pointer from a vector pointer. */
#define map_data(map_ptr)                                                               \
  (struct __map_fp*) (map_ptr - 1) - 1

/**
 * Returns the vector capacity. */
#define map_capacity(map_ptr)                                                           \
  ((map_data(map_ptr))->capacity)

/**
 * Returns the vector length. */
#define map_length(map_ptr)                                                             \
  ((map_data(map_ptr))->length)

/**
 * Returns the size of a map key. */
#define map_key_size(map_ptr)                                                           \
  ((map_data(map_ptr))->key_size)

/**
 * Returns the size of a map value. */
#define map_value_size(map_ptr)                                                         \
  ((map_data(map_ptr))->value_size)

/**
 * Computes the map hash for the given key. */
#define map_hash(map_ptr, key)                                                          \
  ((map_data(map_ptr))->hash(key))

/**
 * Computes the map load factor. */
#define map_load(map_ptr, amount)                                                       \
  ((dec64) (map_length(map_ptr) + amount) / (dec64) map_capacity(map_ptr))

/**
 * Determines if the given index is used in the map. */
#define map_used(map_ptr, index)                                                        \
  ((map_data(map_ptr))->usage)[index]

/**
 * Retrieves the key at the given index using the given type. */
#define map_key(map_ptr, type, index)                                                   \
  ((type*) (map_data(map_ptr))->keys)[index]

/**
 * Configures the hash and compare functions for the map. */
#define map_config(map_ptr, hash_func, compare_func)                                    \
  (map_data(map_ptr))->hash = hash_func;                                                \
  (map_data(map_ptr))->compare = compare_func

/**
 * Configures the key copy behaviour for the map. */
#define map_config_key_copy(map_ptr, length_function, copy_function) (                  \
  (map_data(map_ptr))->copy_keys = true,                                                \
  (map_data(map_ptr))->key_length = length_function,                                    \
  (map_data(map_ptr))->key_copy = copy_function)

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
 * Same as #map_new, but with an arena allocator. */
#define map_new_arena(key_type, value_type, allocator)                                  \
  (map_new_cap_arena(key_type, value_type, MAP_MIN_CAPACITY, allocator))

/**
 * Allocates a new vector using the provided `key_type`, `value_type`
 * and `initial_capacity`. */
#define map_new_cap(key_type, value_type, initial_capacity)                             \
  (map_new_cap_arena(key_type, value_type, MAP_MIN_CAPACITY, NULL))

/**
 *
 * Same as #map_new_cap, but tiwh and arena allocator. */
#define map_new_cap_arena(key_type, value_type, initial_capacity, allocator) (          \
  __map_new(                                                                            \
      map_min_cap(initial_capacity),                                                    \
      allocator,                                                                        \
      sizeof(key_type),                                                                 \
      sizeof(value_type)))

/**
 * Returns `true` if the map has the given key, `false` otherwise. */
#define map_has(map_ptr, key)                                                           \
  (map_find(map_data(map_ptr), key)) > 0)

/**
 * Finds a key in the map. */
#define map_find(map_ptr, key, presence)                                                \
  __map_find(map_data(map_ptr), key, map_hash(map_ptr, key), presence)

/**
 * Sets as used a key in the map. */
#define map_use(map_ptr, key, rehashing)                                                \
  __map_use(map_data(map_ptr), key, map_hash(map_ptr, key), rehashing)

/**
 * Returns the map value associated to the given key. If the key is not present,
 * then the __zero value__ of the map value type is returned. */
#define map_get(map_ptr, key)                                                           \
  (*(map_ptr + (map_find(map_ptr, key, __Map_Find_Pos))))

/**
 * Sets the value for the given key in the map. If the key is already present,
 * the value will be overwritten. */
#define map_set(map_ptr, key, value) (                                                  \
  map_check_rehash(map_ptr, 1) ?                                                        \
  ((*(map_ptr + (map_use(map_ptr, key, __Map_Use_Default))) = value), 1) : 0)

/**
 * Deletes the value for the given key in the map. */
#define map_delete(map_ptr, key)                                                        \
  __map_delete(map_data(map_ptr), key, map_hash(map_ptr, key))

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
        iter_name.hash = (map_data(map_ptr))->hashes[iter_name.index],                  \
        iter_name.used = map_used(map_ptr, iter_name.index), true)

#define map_print(map_ptr, key_type, key_printer, value_type, value_printer)            \
  fprintf(stderr, "\n----\nMap: %p\n----\n", map_ptr);                                  \
  map_all(map_ptr, key_type, value_type, iter) {                                        \
    fprintf(stderr, "[%4li] ", iter.index);                                             \
    fprintf(stderr, "[%12li] ", iter.hash);                                             \
    iter.used ? fprintf(stderr, "[■] ") : fprintf(stderr, "[ ] ");                      \
    fprintf(stderr, "["); key_printer(iter.key); fprintf(stderr, "] ");                 \
    fprintf(stderr, "["); value_printer(iter.value); fprintf(stderr, "]\n");            \
  }

/**
 * Releases all memory regions used by the map. */
#define map_free(map_ptr)                                                               \
  (__map_free(map_data(map_ptr)))


/**
 * This macro shall print a map for debugging purposes. */
#define map_debug(map_ptr, key_type, value_type, key_format, value_format) {            \
  fprintf(stderr, "\nMap %p\n", map_ptr);                                               \
  struct __map_fp* data = map_data(map_ptr);                                            \
                                                                                        \
  fprintf(stderr, "Keys\n");                                                            \
  key_type* key;                                                                        \
  for (uint64 iter = 0; iter < data->capacity; iter++) {                                \
    key = (key_type*) ((byte*) data->keys + (iter * data->key_size));                   \
    fprintf(stderr, "[" key_format "] ", *key);                                         \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
                                                                                        \
  fprintf(stderr, "Usage\n");                                                           \
  for (uint64 iter = 0; iter < data->capacity; iter++) {                                \
    if (data->usage[iter])                                                              \
      fprintf(stderr, "[■] ");                                                          \
    else                                                                                \
      fprintf(stderr, "[ ] ");                                                          \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
                                                                                        \
  fprintf(stderr, "Hashes\n");                                                          \
  for (uint64 iter = 0; iter < data->capacity; iter++) {                                \
    fprintf(stderr, "[%i] ", data->hashes[iter]);                                       \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
                                                                                        \
                                                                                        \
  fprintf(stderr, "Values\n");                                                          \
  value_type* value = NULL;                                                             \
  for (uint64 iter = 0; iter < data->capacity; iter++) {                                \
    value = (value_type*) ((byte*) map_ptr + (iter * data->value_size));                \
    fprintf(stderr, "[" value_format "] ", *value);                                     \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
}

/**
 * This macro shall hex dump the map keys, in order to debug their content. */
#define map_keys_hexdump(map_ptr) {                                                     \
  byte* keys = (byte*) (map_data(map_ptr))->keys;                                       \
  uint64 key_size = map_key_size(map_ptr);                                              \
  uint64 keys_length = map_capacity(map_ptr) * key_size;                                \
  fprintf(stderr, "\n-- Map %p | keys hexdump", map_ptr);                               \
  for (int i = 0; i < keys_length; i++) {                                               \
    if (i % key_size == 0) fprintf(stderr, "\n[%2i] ", i / key_size);                   \
    fprintf(stderr, "%02x ", keys[i]);                                                  \
  }                                                                                     \
  fprintf(stderr, "\n--\n"); }

/**
 * Applies a prebuilt configuration, based on the given *key_type*. */
#define map_prebuilt_config(map_ptr, key_type)                                          \
  if (strcmp(#key_type, "char*") == 0 || strcmp(#key_type, "string") == 0) {            \
    map_config(map_ptr, __map_prebuilt_string_hash, __map__prebuilt_string_compare);    \
    map_config_key_copy(map_ptr, __prebuilt__string_length, __map_prebuilt_string_copy);\
  }
