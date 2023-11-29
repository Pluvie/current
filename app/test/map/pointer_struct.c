void test_map_pointer_struct (
    void
)
{
  describe("[Map] Pointer Struct");

  struct user* users[16] = { 0 };
  int iterations = countof(users) * 3;

  map_new(pointer_struct, struct user*, int,
      .hash = user_hash_ptr,
      .compare = user_compare_ptr);

  for (int i = 0; i < countof(users); i++)
    users[i] = user_generator_ptr(i);

  for (int i = 0; i < iterations; i++)
    map_set(pointer_struct, &users[i % countof(users)], i);

  for(int i = 0; i < countof(users); i++)
    test(map_get(pointer_struct, &users[i % countof(users)]) == (countof(users) * 2) + i);

  //map_keys_hexdump(pointer_struct);
  //map_print(pointer_struct, struct user*, user_print_ptr, int, __map_prebuilt_int32_print);

  map_free(pointer_struct);
  for (int i = 0; i < countof(users); i++)
    free(users[i]);

  success();
}
