void test_map__key_copy__char_ptr__int32 (
    void
)
/**
 * This function shall test map operations on a map with:
 *   key:     `char*`
 *   value:   `int32`
 *
 * With the key copy feature enabled.
 */
{
  describe("[Map][KeyCopy] (char*, int32)");

  /* We will do 100 interations, in which each time the variable `i` will increment from
   * 0 to 99. This variable will be used as a seed to generate a `char*` with the
   * function #string_generator. */
  char forge[16] = { 0 };
  int iterations = 100;

  /* This map will have `char*` as *key* and `char*` as *value*.
   * It will use the prebuilt hash #__map_prebuilt_string_hash and the prebuilt compare
   * #__map_prebuilt_string_compare. */
  map_new(test_map, char*, int32,
    .hash = __map_prebuilt_string_hash,
    .compare = __map_prebuilt_string_compare,
    .copy_keys = true,
    .key_copy_size_func = __map_prebuilt_string_length);

  /* For each iteration, generate a string that will be used both as *key* and *value*
   * of the map. */
  for (int i = 0; i < iterations; i++) {
    int32 generated_string_length = string_generator(forge, sizeof(forge));
    char* key = forge;
    map_set(test_map, &key, generated_string_length);
  }
  map_print(test_map,
    char*, __map_prebuilt_string_print,
    int32, __map_prebuilt_int32_print);

  /* For each *key* in the map, verify that it is equal to its length. */
  map_each(test_map, char*, int32, iter)
    test(map_get(test_map, &iter.key) == strlen(iter.key));

  /* For each *key* in the map, delete it and verify that the map does not have that
   * *key* anymore. */
  map_each(test_map, char*, int32, iter)
    test(
      map_del(test_map, &iter.key) &&
      !map_has(test_map, &iter.key));

  /* Print map content, for debug purposes.
  map_print(test_map,
    char*, __map_prebuilt_string_print,
    char*, __map_prebuilt_string_print); */

  /* Release the map memory. */
  map_free(test_map);

  success();
}
