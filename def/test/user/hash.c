uint64 user_hash (
    void* user
)
{
  return __map_prebuilt_string_hash(((struct user*) user)->name);
}

uint64 user_ptr_hash (
    void* user
)
{
  return __map_prebuilt_string_hash((*(struct user**) user)->name);
}
