struct user user_generator (
    int i
)
/**
 * This function shall generate a stack allocated `struct user` by using the seed *i*,
 * which will determine the user `id`, `age` and `name`.
 *
 * The `name`, will be a 3 char long string, using the seed *i* as char base. */
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
/**
 * This function shall generate a heap allocated `struct user` using the function
 * #user_generator. */
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
/**
 * This function shall generate an arena allocated `struct user` using the function
 * #user_generator. */
{
  struct user user = user_generator(i);
  struct user* user_pointer = arena_calloc(arena, 1, sizeof(struct user));
  memcpy(user_pointer, &user, sizeof(struct user));
  return user_pointer;
}

uint64 user_hash (
    void* user
)
/**
 * This function shall compute an hash using a `struct user` *user*. */
{
  char* user_name = ((struct user*) user)->name;
  return __map_prebuilt_string_hash(&user_name);
}

uint64 user_hash_ptr (
    void* user
)
/**
 * This function shall compute an hash using a `struct user*` *user*. */
{
  char* user_name = (*(struct user**) user)->name;
  return __map_prebuilt_string_hash(&user_name);
}

bool user_compare (
    void* u1,
    void* u2
)
/**
 * This function shall compare two `struct user` *u1* and *u2* and determine if they
 * have the same `name`. */
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp(((struct user*) u1)->name, ((struct user*) u2)->name) == 0;
}

bool user_compare_ptr (
    void* u1,
    void* u2
)
/**
 * This function shall compare two `struct user*` *u1* and *u2* and determine if they
 * have the same `name`. */
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp((*(struct user**) u1)->name, (*(struct user**) u2)->name) == 0;
}

void user_print (
    struct user user
)
/**
 * This function shall print a `struct user` *user*. */
{
  fprintf(stderr, "{%i, %i, %s}", user.id, user.age, user.name);
}

void user_print_ptr (
    struct user* user
)
/**
 * This function shall print a `struct user*` *user*. */
{
  if (user == NULL)
    fprintf(stderr, "-");
  else
    fprintf(stderr, "{%i, %i, %s}", user->id, user->age, user->name);
}
