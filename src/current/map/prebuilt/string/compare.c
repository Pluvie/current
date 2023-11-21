bool __map_prebuilt_string_compare (
    void* s1,
    void* s2
)
/**
 * This function shall compare two keys for a string based hash map and compare them
 * using #strcmp.
 *
 * The first string *s1* is the key to search for, so it is interpreted as a direct
 * char pointer.
 *
 * The second string *s2* is the pointer to the currently iterated key in the keys
 * pointer of the map data. Thus, it is intepreted as a pointer to a char pointer. */
{
  if (s1 == NULL || s2 == NULL) return false;
  return strcmp(*(char**) s1, *(char**) s2) == 0;
}
