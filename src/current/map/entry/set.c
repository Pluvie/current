inline void* map_entry_set (
    Map* map,
    MapEntry* new_entry
)
/**
 * This function shall set corresponding *new_entry* in the map entries.
 *
 * If the *key* is already present in the entries, its value shall be replaced,
 * otherwise a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  size key_size = map->key_size;
  u64 capped_hash = map_capped_hash(new_entry->hash, map->capacity);
  u64 probe_limit = map->probe_limit;
  u64 probe_count = 0;

  MapEntry* entry = map->entries + capped_hash;

linear_probing:
  if (entry->key == NULL)
    return map_entry_add(map, new_entry, entry);

  if (map->flags & MAP_FLAG__FIXED_LOOKUP)
    goto next_entry;

  if (map_compare(entry->key, new_entry->key, key_size)) {
    if (map->flags & MAP_FLAG__COPY_VALUES)
      memcpy(entry->value, new_entry->value, map->value_size);
    else
      entry->value = new_entry->value;

    return entry->value;
  }

next_entry:
  entry++;
  probe_count++;

  if (probe_count >= probe_limit) {
    map_rehash(map);
    return map_entry_set(map, new_entry);
  }

  goto linear_probing;
}
