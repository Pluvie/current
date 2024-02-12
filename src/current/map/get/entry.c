struct map_entry* map_get_entry (
    struct map* map_ptr,
    void* key
)
/**
 * This function shall retrieve the entry of the provided *key* in the map.
 *
 * If the key is not present in the map, `NULL` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map_ptr->key_size;
  u64 hash = map_ptr->hash(key, key_size) % map_ptr->capacity;
  bool (*compare)(void*, void*, size) = map_ptr->compare;
  struct map_entry* entry = map_ptr->buckets[hash];

compare_key:
  if (entry == NULL)
    return NULL;
  if (compare(entry->key, key, key_size))
    return entry;

  entry = entry->next;
  goto compare_key;
}