void test_map__struct_user_ptr__int32 (
    void
)
/**
 * This function shall test map operations on a map with:
 *   key:     `struct user*`
 *   value:   `int32`
 */
{
  describe("[Map] (struct user*, int32)");

  /* We will do 48 interations, in which each time the variable `i` will increment from
   * 0 to 47. This variable will be used as *value*, and as a seed to generate a
   * `struct user*` with the function #user_generator_ptr. */
  struct user* users[16] = { 0 };
  int iterations = countof(users) * 3;

  /* This map will have `struct user*` as *key* and `int` (32bit) as *value*.
   * It will use the custom hash #user_hash_ptr and the custom compare
   * #user_compare_ptr. */
  map_new(test_map, struct user*, int,
      .hash = user_hash_ptr,
      .compare = user_compare_ptr);

  /* Generate a unique user in each element of the `users` array. */
  for (int i = 0; i < countof(users); i++)
    users[i] = user_generator_ptr(i);

  /* For each `i`, set the map *key* equal to the user in the `users` array at position
   * equal to `i % countof(users)`, and the map *value* equal to `i`. */
  for (int i = 0; i < iterations; i++)
    map_set(test_map, &users[i % countof(users)], i);

  /* For each user in the `users` array verify that the map *key* equal to the user
   * is associated to the map *value* equal to `(countof(users) * 2) + i`. */
  for(int i = 0; i < countof(users); i++)
    test(map_get(test_map, &users[i % countof(users)]) == (countof(users) * 2) + i);

  /* For each user in the `users` array verify that the map has a *key* equal to the user
   * then delete it and verify again that the map does not have that *key* anymore. */
  for(int i = 0; i < countof(users); i++)
    test(
      map_has(test_map, &users[i % countof(users)]) &&
      map_del(test_map, &users[i % countof(users)]) &&
      !map_has(test_map, &users[i % countof(users)]));

  /* Print map content, for debug purposes.
  map_print(test_map,
    struct user*, user_print_ptr,
    int, __map_prebuilt_int32_print); */

  /* Release the map memory. */
  map_free(test_map);
  /* Release the generated users memory. */
  for (int i = 0; i < countof(users); i++)
    free(users[i]);

  success();
}
