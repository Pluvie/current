struct user {
  uint32 id;
  uint32 age;
  char name[32];
};

uint32 user_hash (
    void* user
)
{
  return ((struct user*) user)->id;
}

bool user_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return ((struct user*) u1)->id == ((struct user*) u2)->id;
}

void user_print (
    struct user user
)
{
  fprintf(stderr, "{%i, %i, %s}", user.id, user.age, user.name);
}

void benchmark_lookup (
    void
)
{
  fprintf(stderr, "Lookup\n");

  map(struct user, int) user_ages = map_new(struct user, int);
  map_config(user_ages, user_hash, user_compare);
  
  struct user toni = { .id = 11, .age = 33, .name = "Toni" };
  map_set(user_ages, &toni, toni.age);
  fprintf(stderr, ">>> %i\n", map_get(user_ages, &toni));

  map_print(user_ages, struct user, user_print, int, __map_identity_print);

  fprintf(stderr, "CHECK: %i\n", user_ages[0] == 0);
  
  map_free(user_ages);
}
