void test_pointer_struct_arena (
    void
)
{
  struct user* users[16] = { 0 };

  struct arena* scratch = arena_init(
    map_estimated_bytesize(struct user*, int, countof(users)) +
    (countof(users) * sizeof(struct user)));

  map(struct user*, int) pointer_struct = map_new_cap_arena(
    struct user*, int, map_estimated_capacity(countof(users)), scratch);
  map_config(pointer_struct, user_ptr_hash, user_ptr_compare);

  for (int i = 0; i < countof(users); i++)
    users[i] = pointer_user_generator_arena(i, scratch);

  for (int i = 0; i < 100; i++)
    map_set(pointer_struct, &users[i % countof(users)], i);

  for(int i = 84; i < 84 + countof(users); i++)
    assert(map_get(pointer_struct, &users[i % countof(users)]) == i);

  //map_keys_hexdump(pointer_struct);
  //map_print(pointer_struct, struct user*, user_ptr_print, int, __map_prebuilt_int32_print);

  arena_destroy(scratch);
}
