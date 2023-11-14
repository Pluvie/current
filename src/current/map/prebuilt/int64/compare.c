bool __map_prebuilt_int64_compare (
    void* s1,
    void* s2
)
/**
 * This function shall compare two keys and return true if they have the value as
 * `int64`. */
{
  return (*(int64*)s1 == *(int64*)s2);
}
