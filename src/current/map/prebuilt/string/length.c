uint64 __map_prebuilt_string_length (
    void* str
)
/**
 * This function shall return the length of the given *str*. */
{
  if (str == NULL) return 0;
  return strlen(*(char**) str) + 1;
}
