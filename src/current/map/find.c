int64 __map_find (
    struct __map_fp* map_fp,
    void* key,
    uint64 hash,
    enum __map_find_op find_op
)
/**
 * This function shall find the provided *key* in the map.
 *
 * The hash of the key has to be calculated in advance and provided to this function
 * in the *hash* argument. This is an optimization to speed up the rehash function,
 * because this map implementation already stores all the hashed values of the keys.
 *
 * The argument *presence* tweaks the returned value when the key is not present in the
 * map. If *presence* is `true`, then this function returns `-1`, otherwise it
 * returns the key hashed value. This is important to optimize the get / set operations,
 * as the both have to do a lookup on the map, but in the case of a get operation
 * it is important to know if a key is present or not. On the other hand, for a set
 * operation doesn't matter whether the key is present or not, since it has to be
 * written anyway.
 *
 * This funcion shall handle hash collisions using the linear probing technique, which
 * consists in keep looking ahead in the key array until an empty spot is found or the
 * number of iterations reaches the map capacity. */
{
  uint64 capacity = map_fp->capacity;
  uint64 key_size = map_fp->key_size;
  uint64 capped_hash = hash % capacity;
  bool (*compare)(void*, void*) = map_fp->compare;
  bool copied_keys = map_fp->copy_keys;

  void* keys = map_fp->keys;
  void* current_key = NULL;
  int64 pos = -1;
  uint64 iter = 0;
  uint64 offset = capped_hash;
  uint64 max_iter = capacity;

search:
  /* The key is not present, returns this offset only if the *presence* argument is
   * set to `false`, otherwise returns `-1`. */
  if (!map_fp->usage[offset])
    goto not_used;

  /* The key is present, compares it with the provided *key* argument. */
  current_key = (copied_keys)
    ? ((void**) keys)[offset]
    : ((byte*) keys + (key_size * offset));
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
  switch (find_op) {
  case __Map_Find_Offset:
    return offset;
  default:
    return -1;
  }
not_used:
  switch (find_op) {
  case __Map_Find_Offset:
    return offset;
  default:
    return pos;
  }
found:
  return offset;
}
