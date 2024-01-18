uint64 __map_prebuilt_string_hash (
    void* key
)
/**
 * This function returns a hash value for a string based on [djb2]
 * (http://www.cse.yorku.ca/~oz/hash.html) algoritm. */
{
  int character;
  uint64 hash = 5381;
  char* str = *(char**) key;

  while ('\0' != (character = *str++))
    hash = ((hash << 5) + hash) + character; /* hash * 33 + character */

  return hash;
}
