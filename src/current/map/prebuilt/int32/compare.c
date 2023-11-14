bool __map_prebuilt_int32_compare (
    void* s1,
    void* s2
)
/**
 * This function shall compare two keys and return true if they have the value as
 * `int32`. */
{
  return (*(int32*)s1 == *(int32*)s2);
}
