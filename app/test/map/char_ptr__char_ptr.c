void test_map__char_ptr__char_ptr (
    void
)
/**
 * This function shall test map operations on a map with:
 *   key:     `char*`
 *   value:   `char*`
 */
{
  describe("[Map] (char*, char*)");

  /* We will do 100 interations, in which each time the variable `i` will increment from
   * 0 to 99. This variable will be used as a seed to generate a `char*` with the
   * function #string_generator. */
  char forge[16] = { 0 };
  uint32 generated_string_length = 0;
  int iterations = 6;

  /* This map will have `char*` as *key* and `char*` as *value*.
   * It will use the prebuilt hash #__map_prebuilt_string_hash and the prebuilt compare
   * #__map_prebuilt_string_compare. */
  map_new(test_map, char*, char*,
    .hash = __map_prebuilt_string_hash,
    .compare = __map_prebuilt_string_compare);

  /* For each iteration, generate a string that will be used both as *key* and *value*
   * of the map. */
  for (int i = 0; i < iterations; i++) {
    generated_string_length = string_generator(forge, sizeof(forge));
    char* key = calloc(generated_string_length + 1, sizeof(char));
    char* value = calloc(generated_string_length + 1, sizeof(char));
    memcpy(key, forge, generated_string_length);
    memcpy(value, forge, generated_string_length);
    map_set(test_map, &key, value);
  }

  /* For each *key* in the map, verify that it is equal to its associated *value*. */
  map_each(test_map, char*, char*, iter)
    test(strcmp(iter.key, map_get(test_map, &iter.key)) == 0);

  /* For each *key* in the map, delete it and verify that the map does not have that
   * *key* anymore. */
  map_each(test_map, char*, char*, iter) {
    test(
      map_del(test_map, &iter.key) &&
      !map_has(test_map, &iter.key));
    /* Release the memory of the generated strings. */
    free(iter.key);
    free(iter.value);
  }

  /* Print map content, for debug purposes.
  map_print(test_map,
    char*, __map_prebuilt_string_print,
    char*, __map_prebuilt_string_print); */

  /* Release the map memory. */
  map_free(test_map);

  success();
}
