inline void* map_entry_set (
    struct map* map,
    struct map_entry* new_entry
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

  struct map_entry* entry = map->entries + capped_hash;
  //struct map_entry robin = { 0 };

linear_probing:
  if (entry->key == NULL)
    return map_entry_add(map, new_entry, entry);

  if (map->flags & Map_Flag__Fixed_Lookup)
    goto next_entry;

  if (map_compare(entry->key, new_entry->key, key_size)) {
    if (map->flags & Map_Flag__Copy_Values)
      memcpy(entry->value, new_entry->value, map->value_size);
    else
      entry->value = new_entry->value;

    return entry->value;
  }

  //if (new_entry->distance > entry->distance) {
  //  memcpy(&robin, entry, sizeof(struct map_entry));
  //  memcpy(entry, new_entry, sizeof(struct map_entry));
  //  memcpy(new_entry, &robin, sizeof(struct map_entry));
  //}

next_entry:
  entry++;
  probe_count++;
  //new_entry->distance++;

  if (probe_count >= probe_limit) {
    map_rehash(map);
    return map_entry_set(map, new_entry);
  }

  goto linear_probing;
}
