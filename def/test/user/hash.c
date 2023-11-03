uint32 user_hash (
    void* user
)
{
  //return ((struct user*) user)->id;
  return __map_string_key_hash(((struct user*) user)->name);
}
