void __map_prebuilt_string_copy (
    void* s1,
    void* s2,
    uint64 len
)
/**
 * This function shall copy the string *s1* into the *s2*. */
{
  if (s1 == NULL || s2 == NULL) return;
  memcpy(s1, s2, len);
  return;
}
