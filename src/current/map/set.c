void* map_set (
    struct map* map_ptr,
    void* key,
    void* value
)
/**
 * This function shall set corresponding *key* with the provided *value* in the map.
 *
 * If the *key* is already present in the map, its value shall be replaced, otherwise
 * a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  if (key == NULL)
    return NULL;

  u64 hash = map_ptr->hash(key, map_ptr->key_size);
  return map_set_with_buckets(map_ptr, key, value, hash, map_ptr->buckets);
}
