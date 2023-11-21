void test_map_pointer_char (
    void
)
{
  char key_forge[16] = { 0 };
  uint32 generated_string_length = 0;
  int iterations = 4;

  map_new(pointer_char, char*, char*,
    .hash = __map_prebuilt_string_hash,
    .compare = __map_prebuilt_string_compare,
    .copy_keys = true,
    .key_size_func = __map_prebuilt_string_length);

  for (int i = 0; i < iterations; i++) {
    generated_string_length = string_generator(key_forge, sizeof(key_forge));
    char* value_forge = calloc(generated_string_length + 1, sizeof(char));
    memcpy(value_forge, key_forge, generated_string_length);
    map_set(pointer_char, key_forge, value_forge);
  }

  map_print(pointer_char, char*, __map_prebuilt_string_print, char*, __map_prebuilt_string_print);
  map_each(pointer_char, char*, char*, iter) {
    //assert(strcmp(iter.key, map_get(pointer_char, iter.key)) == 0);
    free(iter.value);
  }

  map_free(pointer_char);
}
