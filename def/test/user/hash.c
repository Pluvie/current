uint32 user_hash (
    void* user
)
{
  return __map_string_key_hash(((struct user*) user)->name);
}

uint32 user_ptr_hash (
    void* user
)
{
  return __map_string_key_hash((*(struct user**) user)->name);
}
