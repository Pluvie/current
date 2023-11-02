/**
 * This function returns a hash value for a string based on [djb2]
 * (http://www.cse.yorku.ca/~oz/hash.html) algoritm. */
uint32 __map_string_key_hash (
    void* key
)
{
  int character;
  uint32 hash = 5381;
  char* string = *(char**) key;

  while ('\0' != (character = *string++))
    hash = ((hash << 5) + hash) + character; /* hash * 33 + character */

  return hash;
}
