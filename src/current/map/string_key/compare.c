/**
 * This function shall compare two keys for a string based hash map and compare them
 * using #strcmp. */
bool __map_string_key_compare (
    void* s1,
    void* s2
)
{
  fprintf(stderr, "comparing: %s <-> %s\n", (char*) s1, (char*) s2);
  if (s1 == NULL || s2 == NULL) return false;
  return strcmp((char*) s1, (char*) s2) == 0;
}
