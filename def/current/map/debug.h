/**
 * This macro shall print a map for debugging purposes. */
#define map_debug(map_ptr, key_type, value_type, key_format, value_format) {            \
  fprintf(stderr, "\nMap %p\n", map_ptr);                                               \
  struct __map_data* data = map_data(map_ptr);                                          \
                                                                                        \
  fprintf(stderr, "Keys\n");                                                            \
  key_type* key;                                                                        \
  for (uint32 iter = 0; iter < data->capacity; iter++) {                                \
    key = (key_type*) ((byte*) data->keys + (iter * data->key_size));                   \
    fprintf(stderr, "[" key_format "] ", *key);                                         \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
                                                                                        \
  fprintf(stderr, "Usage\n");                                                           \
  for (uint32 iter = 0; iter < data->capacity; iter++) {                                \
    if (data->usage[iter])                                                              \
      fprintf(stderr, "[■] ");                                                          \
    else                                                                                \
      fprintf(stderr, "[ ] ");                                                          \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
                                                                                        \
  fprintf(stderr, "Hashes\n");                                                          \
  for (uint32 iter = 0; iter < data->capacity; iter++) {                                \
    fprintf(stderr, "[%i] ", data->hashes[iter]);                                       \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
                                                                                        \
                                                                                        \
  fprintf(stderr, "Values\n");                                                          \
  value_type* value = NULL;                                                             \
  for (uint32 iter = 0; iter < data->capacity; iter++) {                                \
    value = (value_type*) ((byte*) map_ptr + (iter * data->value_size));                \
    fprintf(stderr, "[" value_format "] ", *value);                                     \
  }                                                                                     \
  fprintf(stderr, "\n");                                                                \
}

/**
 * This macro shall hex dump the map keys, in order to debug their content. */
#define map_keys_hexdump(map_ptr) {                                                     \
  byte* keys = (byte*) (map_data(map_ptr))->keys;                                       \
  uint32 key_size = map_key_size(map_ptr);                                              \
  uint32 keys_length = map_capacity(map_ptr) * key_size;                                \
  fprintf(stderr, "\n-- Map %p | keys hexdump", map_ptr);                               \
  for (int i = 0; i < keys_length; i++) {                                               \
    if (i % key_size == 0) fprintf(stderr, "\n[%2i] ", i / key_size);                   \
    fprintf(stderr, "%02x ", keys[i]);                                                  \
  }                                                                                     \
  fprintf(stderr, "\n--\n"); }
