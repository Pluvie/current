struct user user_generator (
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
//
//struct user scalar_user_generator (
//    int i
//)
//{
//  return user_generator(i);
//}
//
//struct user* pointer_user_generator (
//    int i
//)
//{
//  struct user user = user_generator(i);
//  struct user* user_pointer = calloc(1, sizeof(struct user));
//  memcpy(user_pointer, &user, sizeof(struct user));
//  return user_pointer;
//}
//
//struct user* pointer_user_generator_arena (
//    int i,
//    struct arena* arena
//)
//{
//  struct user user = user_generator(i);
//  struct user* user_pointer = arena_calloc(arena, 1, sizeof(struct user));
//  memcpy(user_pointer, &user, sizeof(struct user));
//  return user_pointer;
//}

uint64 user_hash (
    void* user
)
{
  return __map_prebuilt_string_hash(((struct user*) user)->name);
}

bool user_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp(((struct user*) u1)->name, ((struct user*) u2)->name) == 0;
}

void user_print (
    struct user user
)
{
  fprintf(stderr, "{%i, %i, %s}", user.id, user.age, user.name);
}
