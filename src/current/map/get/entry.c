struct map_entry* map_get_entry (
    struct map* map,
    void* key
)
/**
 * This function shall retrieve the entry of the provided *key* in the map.
 *
 * If the key is not present in the map, `NULL` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map->key_size;
  u64 hash = map->hash(key, key_size) % map->capacity;
  bool (*compare)(void*, void*, size) = map->compare;
  struct map_entry* entry = map->buckets[hash];

compare_key:
  if (entry == NULL)
    return NULL;
  if (compare(entry->key, key, key_size))
    return entry;

  entry = entry->next;
  goto compare_key;
}
