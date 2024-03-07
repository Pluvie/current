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
  u32 probe_limit = map->probe_limit;
  u32 probe_count = 0;
  u64 hash = map_hash(key, key_size);
  u64 capped_hash = map_capped_hash(hash, map->capacity);

  struct map_entry* entry = map->entries + capped_hash;

linear_probing:
  if (entry->key == NULL)
    return NULL;

  if (map_compare(entry->key, key, key_size))
    return entry;

  entry++;
  probe_count++;

  if (probe_count >= probe_limit)
    return NULL;

  goto linear_probing;
}
