void* map_entry_add (
    struct map* map,
    struct map_entry* entry,
    void* key,
    void* value,
    u64 hash
)
/**
 * This function shall add a new entry in the map, with the provided *key*, *value* and
 * *hash*.
 *
 * The entry will be stored at the provided *entry* location, which must be an entry
 * pointer address. In other words, the caller of this function must know in advance
 * where the new entry must be added: this function will not do any reasoning in this
 * matter.
 *
 * If, after adding the new entry, the map load reaches or surpasses the
 * `MAP_MAXIMUM_LOAD_FACTOR` threshold, then this function shall trigger a rehash,
 * invoking the #map_rehash function.
 *
 * The function will return the provided *value*. */
{
  map_entry_key_set(map, entry, key);
  map_entry_value_set(map, entry, value);
  entry->hash = hash;

  map->length++;

  /* Skips load check if already rehashing. */
  if (map->flags & Map_Flag__Rehashing)
    return value;

  d64 map_load = (d64) map->length / (d64) map->capacity;
  if (map_load >= MAP_MAXIMUM_LOAD_FACTOR)
    map_rehash(map);

  return value;
}
