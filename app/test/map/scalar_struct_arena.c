void test_scalar_struct_arena (
    void
)
{
  struct arena* scratch = arena_init(map_estimated_bytesize(struct user, int, 100));

  map(struct user, int) scalar_struct = map_new_cap_arena(
    struct user, int, map_estimated_capacity(100), scratch);
  map_config(scalar_struct, user_hash, user_compare);

  struct user user = { 0 };
  for (int i = 0; i < 100; i++) {
    user = scalar_user_generator(i);
    map_set(scalar_struct, &user, i);
  }

  for (int i = 74; i < 74 + 26; i++) {
    user = scalar_user_generator(i);
    assert(map_get(scalar_struct, &user) == i);
  }

  //map_print(scalar_struct, struct user, user_print, int, __map_prebuilt_int32_print);
  arena_destroy(scratch);
}
