int64 __map_find (
    struct __map_fp* map_fp,
    void* key,
    uint64 hash,
    enum __map_find_output find_output
)
/**
 * This function shall find the provided *key* in the map.
 *
 * The hash of the key has to be calculated in advance and provided to this function
 * in the *hash* argument. This is an optimization to speed up the rehash function,
 * because Current map implementation already stores all the hashed values of the keys.
 *
 * The argument *find_output* tweaks the returned value of this function, depending
 * on whether the key is found in the map. These are the possible outputs, where
 * `offset` indicates the position of the key in the key array:
 *
 *  - `__Map_Find_Default` returns:
 *    - `-1` if not found.
 *    - `-1` if found but not used.
 *    - `offset` if found.
 *  - `__Map_Find_Offset` returns
 *    - `offset` if not found.
 *    - `offset` if found but not used.
 *    - `offset` if found.
 *
 * This funcion shall handle hash collisions using the linear probing technique, which
 * consists in keep looking ahead in the key array until an empty spot is found or the
 * number of iterations reaches the map capacity. */
{
  uint64 capacity = map_fp->capacity;
  uint64 capped_hash = hash % capacity;

  uint64 key_size = map_fp->config.key_size;
  bool (*compare)(void*, void*) = map_fp->config.compare;

  void* keys = map_fp->keys;
  void* current_key = NULL;
  uint64 iter = 0;
  uint64 offset = capped_hash;
  uint64 max_iter = capacity;

search:
  /* The key is not present, returns this offset only if the *presence* argument is
   * set to `false`, otherwise returns `-1`. */
  if (!map_fp->usage[offset])
    goto not_used;

  /* The key is present, compares it with the provided *key* argument. */
  current_key = (byte*) keys + (key_size * offset);
  if (compare(key, current_key))
    goto found;

  iter++;
  offset++;

  /* Starts again from the beginning of the key array if the end was reached. */
  if (offset >= capacity)
    offset = 0;
  /* Stops the search if more iterations than the map capacity have been done. */
  if (iter > max_iter)
    goto not_found;

  /* Searches the next key. */
  goto search;

not_found:
  switch (find_output) {
  case __Map_Find_Offset:
    return offset;
  default:
    return -1;
  }
not_used:
  switch (find_output) {
  case __Map_Find_Offset:
    return offset;
  default:
    return -1;
  }
found:
  return offset;
}
