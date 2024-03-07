void* map_set_with_hash (
    struct map* map,
    void* key,
    void* value,
    u64 hash
)
/**
 * This function shall set corresponding *key* with the provided *value* in the
 * map entries, using the precalculated *hash*.
 *
 * If the *key* is already present in the entries, its value shall be replaced,
 * otherwise a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  size key_size = map->key_size;
  u32 probe_limit = map->probe_limit;
  u32 probe_count = 0;
  u64 capped_hash = map_capped_hash(hash, map->capacity);

  struct map_entry* entry = map->entries + capped_hash;
  if (entry->key == NULL)
    return map_entry_add(map, entry, key, value, hash);

linear_probing:
  if (probe_count >= probe_limit) {
    map_rehash(map);
    return map_set(map, key, value);
  }

  if (map_compare(entry->key, key, key_size)) {
    map_entry_value_set(map, entry, value);
    return value;
  }

  entry++;
  goto linear_probing;
}
