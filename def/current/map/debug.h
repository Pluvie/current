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
