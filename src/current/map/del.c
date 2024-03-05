void* map_del (
    struct map* map,
    void* key
)
/**
 * This function shall delete the *provided* key in the map.
 *
 * If the key is found, its value shall be returned.
 * If not, `NULL` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map->key_size;
  u64 hash = map_hash(key, key_size);
  u64 capped_hash = map_capped_hash(hash, map->capacity);
  struct map_entry* entry = map->buckets[capped_hash];
  struct map_entry* previous_entry = NULL;
  void* deleted_value = NULL;

compare_key:
  if (entry == NULL)
    return NULL;
  if (map_compare(entry->key, key, key_size)) {
    deleted_value = entry->value;
    goto delete_entry;
  }

  previous_entry = entry;
  entry = entry->next;
  goto compare_key;

delete_entry:
  if (previous_entry == NULL)
    map->buckets[capped_hash] = entry->next;
  else
    previous_entry->next = entry->next;

  map_free_entry(map, entry);
  return deleted_value;
}
