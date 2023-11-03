/**
 * This function shall print a string key. */
void __map_string_key_print (
    char* key
)
{
  if (key == NULL)
    fprintf(stderr, "%-16s", "");
  else
    fprintf(stderr, "%-16s", key);
}
