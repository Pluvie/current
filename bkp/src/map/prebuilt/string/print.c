void __map_prebuilt_string_print (
    char* key
)
/**
 * This function shall print a string key or value. */
{
  if (key == NULL)
    fprintf(stderr, "%-16s", "");
  else
    fprintf(stderr, "%-16s", key);
}
