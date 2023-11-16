void test_char_pointer_arena (
    void
)
{
  char key_forge[16] = { 0 };

  struct arena* scratch = arena_init(
    map_estimated_bytesize(char*, char*, 100) +
    (100 * sizeof(key_forge)) +
    (100 * sizeof(key_forge)));

  map(char*, char*) char_pointer = map_new_cap_arena(
    char*, char*, map_estimated_capacity(100), scratch);
  map_prebuilt_config(char_pointer, char*);

  char character = 'a';
  uint32 string_length = 0;

  for (int i = 0; i < 100; i++) {
    memset(key_forge, '\0', sizeof(key_forge));
    string_length = (i % lengthof(key_forge)) + 1;

    for (int c = 0; c < string_length; c++) {
      key_forge[c] = character;
      character++;
      if (character > 'z')
        character = 'a';
    }

    char* value_forge = arena_calloc(scratch, 1, string_length + 1);
    memcpy(value_forge, key_forge, string_length);
    map_set(char_pointer, key_forge, value_forge);
  }

  //map_print(char_pointer, char*, __map_prebuilt_string_print, char*, __map_prebuilt_string_print);
  map_each(char_pointer, char*, char*, iter)
    assert(strcmp(iter.key, map_get(char_pointer, iter.key)) == 0);

  arena_destroy(scratch);
}
