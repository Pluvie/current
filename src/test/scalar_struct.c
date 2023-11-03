struct user scalar_user_generator (
    int i
)
{
  char c = (i % 26) + 97;
  struct user user = {
    .id = i,
    .age = i,
    .name =  { c, c, c } };
  return user;
}

void test_scalar_struct (
    void
)
{
  map(struct user, int) scalar_struct = map_new(struct user, int);
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

  //map_print(scalar_struct, struct user, user_print, int, __map_identity_print);
  map_free(scalar_struct);
}
