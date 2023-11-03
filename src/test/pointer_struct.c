struct user* pointer_user_generator (
    int i
)
{
  char c = (i % 26) + 97;
  struct user user = {
    .id = i,
    .age = i,
    .name =  { c, c, c } };
  struct user* user_pointer = calloc(1, sizeof(struct user));
  memcpy(user_pointer, &user, sizeof(struct user));
  return user_pointer;
}

void test_pointer_struct (
    void
)
{
  map(struct user*, int) pointer_struct = map_new(struct user*, int);
  map_config(pointer_struct, user_ptr_hash, user_ptr_compare);

  struct user* users[16] = { 0 };
  for (int i = 0; i < countof(users); i++)
    users[i] = pointer_user_generator(i);

  for (int i = 0; i < 100; i++)
    map_set(pointer_struct, &users[i % countof(users)], i);

  for(int i = 84; i < 84 + countof(users); i++)
    assert(map_get(pointer_struct, &users[i % countof(users)]) == i);

  //map_keys_hexdump(pointer_struct);
  //map_print(pointer_struct, struct user*, user_ptr_print, int, __map_identity_print);

  map_free(pointer_struct);
  for (int i = 0; i < countof(users); i++)
    free(users[i]);
}