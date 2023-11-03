bool user_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp(((struct user*) u1)->name, ((struct user*) u2)->name) == 0;
}

bool user_ptr_compare (
    void* u1,
    void* u2
)
{
  if (u1 == NULL || u2 == NULL) return false;
  return strcmp((*(struct user**) u1)->name, (*(struct user**) u2)->name) == 0;
}
