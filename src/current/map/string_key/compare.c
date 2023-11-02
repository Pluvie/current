bool __map_string_key_compare (
    void* s1,
    void* s2
)
{
  if (s1 == NULL || s2 == NULL) return false;
  return strcmp(s1, s2) == 0;
}
