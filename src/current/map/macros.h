/**
 * Returns the map fat pointer from a map pointer. */
#define map_fp(map_ptr)                                                                 \
  (struct __map_fp*) (map_ptr - 1) - 1

/**
 * Initializes an already declared map, with the given *name*, *key_type* and
 * *value_type*. Extra configuration options may be passed using the macro variadic
 * args. */
#define map_init(name, key_type, value_type, ...)                                       \
  {                                                                                     \
    struct __map_config config = {                                                      \
      .key_size = sizeof(key_type),                                                     \
      .value_size = sizeof(value_type),                                                 \
      ##__VA_ARGS__ };                                                                  \
    name = __map_new(config);                                                           \
  }

/**
 * Creates a new map, with the given *name*, *key_type* and *value_type*.
 * Extra configuration options may be passed using the macro variadic args. */
#define map_new(name, key_type, value_type, ...)                                        \
  map(key_type, value_type) name;                                                       \
  map_init(name, key_type, value_type, ##__VA_ARGS__ )

/**
 * Returns the vector capacity. */
#define map_capacity(map_ptr)                                                           \
  ((map_fp(map_ptr))->capacity)

/**
 * Returns the vector length. */
#define map_length(map_ptr)                                                             \
  ((map_fp(map_ptr))->length)

/**
 * Returns the memory footprint of a map. */
#define map_memsize(key_type, value_type, initial_capacity)                             \
  (__map_calc_memsize(sizeof(key_type), sizeof(value_type), initial_capacity).footprint)

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
#define map_set(map_ptr, key, value) (                                                  \
  map_load(map_ptr, 1) >= 0.7                                                           \
    ? ((map_ptr = __map_rehash(map_ptr, map_fp(map_ptr))),                              \
      (*(map_ptr + (map_use(map_ptr, key, __Map_Use_Default))) = value),                \
      value)                                                                            \
    : ((*(map_ptr + (map_use(map_ptr, key, __Map_Use_Default))) = value),               \
      value))

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
