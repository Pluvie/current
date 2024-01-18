/**
 * Map internal function declarations. */

function(__map_calc_memsize, struct __map_memsize) (uint16, uint16, uint64);
function(__map_delete_key, bool) (void*, uint64, struct __map_fat_ptr*);
function(__map_free, void) (struct __map_fat_ptr*);
function(__map_get_key_offset, int64) (void*, uint64, struct __map_fat_ptr*, enum __map_find_output);
function(__map_new, void*) (struct __map_config);
function(__map_rehash, void*) (void*, struct __map_fat_ptr*);
function(__map_set_key_value, int64) (void*, uint64, struct __map_fat_ptr*, enum __map_use_opmode);

/**
 * Returns the map fat pointer from a map pointer. */
#define map_fat_ptr(map_ptr)                                                            \
  ((struct __map_fat_ptr*) (map_ptr - 1) - 1)

/**
 * Returns the map capacity. */
#define map_capacity(map_ptr)                                                           \
  ((map_fat_ptr(map_ptr))->capacity)

/**
 * Returns the map length. */
#define map_length(map_ptr)                                                             \
  ((map_fat_ptr(map_ptr))->length)

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
  (map_fat_ptr(map_ptr)->config.hash(&(key)))

/**
 * Retrieves the map stored hash for the given key offset. */
#define map_hash_stored(map_ptr, offset)                                                \
  ((map_fat_ptr(map_ptr)->hashes)[offset])

/**
 * Retrieves the key at the given index using the given type. */
#define map_key(map_ptr, type, index)                                                   \
  (((type*) (map_fat_ptr(map_ptr))->keys)[index])

/**
 * Determines if the given index is used in the map. */
#define map_used(map_ptr, index)                                                        \
  ((map_fat_ptr(map_ptr)->statuses)[index] == __Map__Key_Status__Used)

/**
 * Finds a key in the map. */
#define map_find(map_ptr, key, find_output)                                             \
  __map_find(&(key), map_hash(map_ptr, key), map_fat_ptr(map_ptr), find_output)

/**
 * Sets as used a key in the map. */
#define map_use(map_ptr, key, use_opmode)                                               \
  __map_use(&(key), map_hash(map_ptr, key), map_fat_ptr(map_ptr), use_opmode)

/**
 * Prints the map, using the provided printers for keys and values. */
#define map_print(map_ptr, key_type, key_printer, value_type, value_printer)            \
  fprintf(stderr, "\n----\nMap: %p\n----\n", map_ptr);                                  \
  fprintf(stderr, "index   hash                              used\n");                  \
  for map_all(map_ptr, key_type, value_type, iter) {                                    \
    fprintf(stderr, "[%4li] ", iter.index);                                             \
    fprintf(stderr, "[%32li] ", iter.hash);                                             \
    iter.used ? fprintf(stderr, "[■] ") : fprintf(stderr, "[ ] ");                      \
    fprintf(stderr, "["); key_printer(iter.key); fprintf(stderr, "] ");                 \
    fprintf(stderr, "["); value_printer(iter.value); fprintf(stderr, "]\n");            \
  }

/**
 * This macro shall hex dump the map keys, in order to debug their content. */
#define map_keys_hexdump(map_ptr) {                                                     \
  byte* keys = (map_fat_ptr(map_ptr))->keys;                                    \
  uint64 key_size = (map_fat_ptr(map_ptr))->config.key_size;                            \
  uint64 keys_length = map_capacity(map_ptr) * key_size;                                \
  fprintf(stderr, "\n-- Map %p | keys hexdump", map_ptr);                               \
  for (int i = 0; i < keys_length; i++) {                                               \
    if (i % key_size == 0) fprintf(stderr, "\n[%2li] ", i / key_size);                  \
    fprintf(stderr, "%02x ", keys[i]);                                                  \
  }                                                                                     \
  fprintf(stderr, "\n--\n"); }
