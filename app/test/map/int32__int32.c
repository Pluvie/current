void test_map__int32__int32 (
    void
)
/**
 * This function shall test map operations on a map with:
 *   key:     `int32`
 *   value:   `int32`
 */
{
  describe("[Map] (int32, int32)");

  /* We will do 100 interations, in which each time the variable `i` will increment from
   * 0 to 99. This variable will be used both as *key* and *value*. */
  int iterations = 4;

  /* This map will have `int` (32bit) as *key* and `int` (32bit) as *value*.
   * It will also use the prebuilt hash and compare function for int32 type. */
  map_new(test_map, int, int,
    .hash = __map_prebuilt_int32_hash,
    .compare = __map_prebuilt_int32_compare);

  /* For each `i`, set the map *key* equal to `i` and the map *value* equal to `i`. */
  for (int i = 0; i < iterations; i++)
    map_set(test_map, i, i);

  /* For each `i`, verify that the map *key* equal to `i` is associated to the map
   * *value* equal to `i`. */
  for (int i = 0; i < iterations; i++)
    test(map_get(test_map, i) == i);
  map_print(test_map,
    int, __map_prebuilt_int32_print,
    int, __map_prebuilt_int32_print);

  /* For each `i`, verify that the map has a *key* equal to `i`, then delete it, and
   * verify again that the map does not have that *key* anymore. */
  for (int i = 0; i < iterations; i++) {
    fprintf(stderr, "\n---> %i \n %i\n", i, map_has(test_map, i));
    test(
      map_has(test_map, i) &&
      map_del(test_map, i) &&
      !map_has(test_map, i));
  }

  /* Print map content, for debug purposes.
  map_print(test_map,
    int, __map_prebuilt_int32_print,
    int, __map_prebuilt_int32_print); */

  /* Release the map memory. */
  map_free(test_map);

  success();
}
