void test_map_pointer_char (
    void
)
{
  char forge[16] = { 0 };
  uint32 generated_string_length = 0;
  int iterations = 100;

  map_new(pointer_char, char*, char*,
    .hash = __map_prebuilt_string_hash,
    .compare = __map_prebuilt_string_compare);

  for (int i = 0; i < iterations; i++) {
    generated_string_length = string_generator(forge, sizeof(forge));
    char* key = calloc(generated_string_length + 1, sizeof(char));
    char* value = calloc(generated_string_length + 1, sizeof(char));
    memcpy(key, forge, generated_string_length);
    memcpy(value, forge, generated_string_length);
    map_set(pointer_char, &key, value);
  }

  //map_print(pointer_char, char*, __map_prebuilt_string_print, char*, __map_prebuilt_string_print);
  map_each(pointer_char, char*, char*, iter)
    assert(strcmp(iter.key, map_get(pointer_char, &iter.key)) == 0);

  map_each(pointer_char, char*, char*, iter) {
    free(iter.key);
    free(iter.value);
  }
  map_free(pointer_char);
}
