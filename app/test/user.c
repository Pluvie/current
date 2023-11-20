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

struct user* user_generator_ptr (
    int i
)
{
  struct user user = user_generator(i);
  struct user* user_pointer = calloc(1, sizeof(struct user));
  memcpy(user_pointer, &user, sizeof(struct user));
  return user_pointer;
}

struct user* user_generator_ptr_arena (
    int i,
    struct arena* arena
)
{
  struct user user = user_generator(i);
  struct user* user_pointer = arena_calloc(arena, 1, sizeof(struct user));
  memcpy(user_pointer, &user, sizeof(struct user));
  return user_pointer;
}

uint64 user_hash (
    void* user
)
{
  return __map_prebuilt_string_hash(((struct user*) user)->name);
}

uint64 user_hash_ptr (
    void* user
)
{
  return __map_prebuilt_string_hash((*(struct user**) user)->name);
}

bool user_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp(((struct user*) u1)->name, ((struct user*) u2)->name) == 0;
}

bool user_compare_ptr (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp((*(struct user**) u1)->name, (*(struct user**) u2)->name) == 0;
}

void user_print (
    struct user user
)
{
  fprintf(stderr, "{%i, %i, %s}", user.id, user.age, user.name);
}

void user_print_ptr (
    struct user* user
)
{
  if (user == NULL)
    fprintf(stderr, "-");
  else
    fprintf(stderr, "{%i, %i, %s}", user->id, user->age, user->name);
}
