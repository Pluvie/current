/**
 * This function shall compare two keys and return true if they have the same memory
 * address. */
bool __map_identity_compare (
    void* s1,
    void* s2
)
{
  return (*(int*)s1 == *(int*)s2);
}
