void test_char_pointer (
    void
)
{
  map(char*, char*) char_pointer = map_new(char*, char*);
  map_prebuilt_config(char_pointer, char*);

  char character = 'a';
  char key_forge[16] = { 0 };
  uint32 string_length = 0;

  for (int i = 0; i < 10; i++) {
    memset(key_forge, '\0', sizeof(key_forge));
    string_length = (i % lengthof(key_forge)) + 1;

    for (int c = 0; c < string_length; c++) {
      key_forge[c] = character;
      character++;
      if (character > 'z')
        character = 'a';
    }

    map_set(char_pointer, key_forge, strdup(key_forge));
  }

  //map_print(char_pointer, char*, __map_prebuilt_string_print, char*, __map_prebuilt_string_print);
  map_each(char_pointer, char*, char*, iter) {
    assert(strcmp(iter.key, map_get(char_pointer, iter.key)) == 0);
    free(iter.value);
  }

  map_free(char_pointer);
}
