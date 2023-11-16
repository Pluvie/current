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

struct user scalar_user_generator (
    int i
)
{
  return user_generator(i);
}

struct user* pointer_user_generator (
    int i
)
{
  struct user user = user_generator(i);
  struct user* user_pointer = calloc(1, sizeof(struct user));
  memcpy(user_pointer, &user, sizeof(struct user));
  return user_pointer;
}

struct user* pointer_user_generator_arena (
    int i,
    struct arena* arena
)
{
  struct user user = user_generator(i);
  struct user* user_pointer = arena_calloc(arena, 1, sizeof(struct user));
  memcpy(user_pointer, &user, sizeof(struct user));
  return user_pointer;
}
