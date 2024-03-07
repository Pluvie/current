void* map_set (
    struct map* map,
    void* key,
    void* value
)
/**
 * This function shall set corresponding *key* with the provided *value* in the
 * map entries.
 *
 * If the *key* is already present in the entries, its value shall be replaced,
 * otherwise a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  if (key == NULL)
    return NULL;

  u64 hash = map_hash(key, map->key_size);
  return map_set_with_hash(map, key, value, hash);
}
