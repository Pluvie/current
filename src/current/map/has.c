bool map_has (
    struct map* map,
    void* key
)
/**
 * This function shall determine if the provided *key* is present in the map.
 *
 * If the key is present in the map, `true` shall be returned.
 * If the key is not present in the map, `false` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map->key_size;
  u64 hash = map_hash(key, key_size) % map->capacity;
  struct map_entry* entry = map->buckets[hash];

compare_key:
  if (entry == NULL)
    return false;
  if (map_compare(entry->key, key, key_size))
    return true;

  entry = entry->next;
  goto compare_key;
}
