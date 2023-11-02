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
 * This function shall save the find results in the `find` struct of the map data,
 * using the following fields:
 *
 *  - `find.pos`: stores the returned value of the function.
 *  - `find.hash`: stores the provided hashed value of the key.
 *  - `find.offset`: stores the actual index in the value array, which may be different
 *    from the capped hash due to collisions.
 *
 * Speaking of collisions, this funcion shall handle them using the linear probing
 * technique, which consists in keep looking ahead in the key array until an empty
 * spot is found or the number of iterations reaches the map capacity. */
int32 __map_find (
    struct __map_data* data,
    void* key,
    uint32 hash,
    bool presence
)
{
  uint32 capacity = data->capacity;
  uint32 key_size = data->key_size;
  uint32 capped_hash = hash % data->capacity;
  bool (*compare)(void*, void*) = data->compare;

  uint32 offset = capped_hash;
  void* current_key = NULL;
  int32 pos = -1;

  uint32 iter = 0;
  uint32 max_iter = capacity;

search:
  /* The key is not present, returns this offset only if the *presence* argument is
   * set to `false`, otherwise returns `-1`. */
  if (!data->usage[offset])
    goto not_used;

  /* The key is present, compares it with the provided *key* argument. */
  current_key = ((byte*) data->keys + (key_size * offset));
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
  pos = -1;
  goto end;
not_used:
  pos = presence ? -1 : offset;
  goto end;
found:
  pos = offset;
  goto end;

end:
  data->find.pos = pos;
  data->find.hash = hash;
  data->find.offset = offset;
  return pos;
}
