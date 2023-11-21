void test_map_pointer_char_key_copy (
    void
)
{
  char forge[16] = { 0 };
  int iterations = 100;

  map_new(pointer_char, char*, char*,
    .hash = __map_prebuilt_string_hash,
    .compare = __map_prebuilt_string_compare,
    .copy_keys = true,
    .key_size_func = __map_prebuilt_string_length);

  for (int i = 0; i < iterations; i++) {
    string_generator(forge, sizeof(forge));
    char* key = forge;
    map_set(pointer_char, &key, forge);
  }

  //map_print(pointer_char, char*, __map_prebuilt_string_print, char*, __map_prebuilt_string_print);
  map_each(pointer_char, char*, char*, iter)
    assert(strcmp(forge, map_get(pointer_char, &iter.key)) == 0);

  map_free(pointer_char);
}
