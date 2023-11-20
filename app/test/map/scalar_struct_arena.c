void test_map_scalar_struct_arena (
    struct arena* arena
)
{
  int iterations = 26 * 3;
  struct user user = { 0 };

  map_new(scalar_struct, struct user, int,
      .arena = arena,
      .hash = user_hash,
      .compare = user_compare);
  for (int i = 0; i < iterations; i++) {
    user = user_generator(i);
    map_set(scalar_struct, &user, i);
  }

  int i = 0;
  for (char c = 'a'; c <= 'z'; c++) {
    i = (int) c - 45;
    user = user_generator(i);
    assert(map_get(scalar_struct, &user) == i);
  }

  //map_print(scalar_struct, struct user, user_print, int, __map_prebuilt_int32_print);
}
