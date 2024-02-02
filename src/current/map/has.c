bool map_has (
    struct map* map_ptr,
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

  size key_size = map_ptr->key_size;
  u64 hash = map_ptr->hash(key, key_size) % map_ptr->capacity;
  bool (*compare)(void*, void*, size) = map_ptr->compare;
  struct map_entry* entry = map_ptr->buckets[hash];

compare_key:
  if (entry == NULL)
    return false;
  if (compare(entry->key, key, key_size))
    return true;

  entry = entry->next;
  goto compare_key;
}
