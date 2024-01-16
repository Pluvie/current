void test_map__int64__int64 (
    void
)
/**
 * This function shall test map operations on a map with:
 *   key:     `int64`
 *   value:   `int64`
 */
{
  describe("[Map] (int64, int64)");

  /* We will do 100 interations, in which each time the variable `i` will increment from
   * base + 0 to base + 99. This variable will be used both as *key* and *value*.
   * The base value is equal to 1 bitshifted by 44 positions (1,759218604×10¹³), just
   * to have a high `int64` value to test. */
  int iterations = 100;
  int64 base = 1UL << 44;

  /* This map will have `int` (64bit) as *key* and `int` (64bit) as *value*.
   * It will also use the prebuilt hash and compare function for int64 type. */
  map_new(test_map, int64, int64,
    .hash = __map_prebuilt_int64_hash,
    .compare = __map_prebuilt_int64_compare);

  /* For each `i`, set the map *key* equal to `i` and the map *value* equal to `i`. */
  for (int64 i = base; i < base + iterations; i++)
    map_set(test_map, i, i);

  /* For each `i`, verify that the map *key* equal to `i` is associated to the map
   * *value* equal to `i`. */
  for (int64 i = base; i < base + iterations; i++)
    test(map_get(test_map, i) == i);

  /* For each `i`, verify that the map has a *key* equal to `i`, then delete it, and
   * verify again that the map does not have that *key* anymore. */
  for (int64 i = base; i < base + iterations; i++)
    test(
      map_has(test_map, i) &&
      map_del(test_map, i) &&
      !map_has(test_map, i));

  /* Print map content, for debug purposes.
  map_print(test_map,
    int64, __map_prebuilt_int64_print,
    int64, __map_prebuilt_int64_print); */

  /* Release the map memory. */
  map_free(test_map);

  success();
}
