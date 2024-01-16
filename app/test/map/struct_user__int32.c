void test_map__struct_user__int32 (
    void
)
/**
 * This function shall test map operations on a map with:
 *   key:     `struct user`
 *   value:   `int32`
 */
{
  describe("[Map] (struct user, int32)");

  /* We will do 78 interations, in which each time the variable `i` will increment from
   * 0 to 77. This variable will be used as *value*, and as a seed to generate a
   * `struct user` with the function #user_generator. */
  int iterations = 26 * 3;
  struct user user = { 0 };

  /* This map will have `struct user` as *key* and `int` (32bit) as *value*.
   * It will use the custom hash #user_hash and the custom compare #user_compare. */
  map_new(test_map, struct user, int,
      .hash = user_hash,
      .compare = user_compare);

  /* For each `i`, generate a `struct user` with seed equal to `i` and set the map *key*
   * equal to the generated user and the map *value* equal to `i`. */
  for (int i = 0; i < iterations; i++) {
    user = user_generator(i);
    map_set(test_map, user, i);
  }

  /* For each `c` from 'a' to 'z', verify that the map *key* equal to the generated user
   * `c` is associated to the map *value* from 56 to 77. */
  for (char c = 'a'; c <= 'z'; c++) {
    user = user_generator((int) c - 45);
    test(map_get(test_map, user) == ((int) c - 45));
  }

  /* For each `c` from 'a' to 'z', verify that the map has the *key* equal to the
   * generated user, then delete it and verify again that the map does not have that
   * *key* anymore. */
  for (char c = 'a'; c <= 'z'; c++) {
    user = user_generator((int) c - 45);
    test(
      map_has(test_map, user) &&
      map_del(test_map, user) &&
      !map_has(test_map, user));
  }

  /* Print map content, for debug purposes.
  map_print(test_map,
    struct user, user_print,
    int, __map_prebuilt_int32_print); */

  /* Release the map memory. */
  map_free(test_map);

  success();
}
