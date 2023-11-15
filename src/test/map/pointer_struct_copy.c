void test_pointer_struct_copy (
    void
)
{
  map(struct user*, int) pointer_struct = map_new(struct user*, int);
  map_config(pointer_struct, user_hash, user_compare);
  map_config_key_copy_fixlen(pointer_struct, sizeof(struct user));

  struct user* users[16] = { 0 };
  for (int i = 0; i < countof(users); i++)
    users[i] = pointer_user_generator(i);

  for (int i = 0; i < 100; i++)
    map_set(pointer_struct, users[i % countof(users)], i);

  for(int i = 84; i < 84 + countof(users); i++)
    assert(map_get(pointer_struct, users[i % countof(users)]) == i);

  //map_keys_hexdump(pointer_struct);
  //map_print(pointer_struct, struct user*, user_ptr_print, int, __map_prebuilt_int32_print);

  map_free(pointer_struct);
  for (int i = 0; i < countof(users); i++)
    free(users[i]);
}
