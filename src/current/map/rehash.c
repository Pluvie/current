void map_rehash (
    struct map* map
)
/**
 * This function shall double the map capacity and shall reposition all entries in their
 * new hashed location.
 *
 * This operation is necessary in order to avoid overcrowding of the map: when this
 * happens, the map performances start to degrade, because the entries will start to
 * overcrowd, requiring more linear probing in order to find the entries.
 *
 * Increasing the capacity and redistributing the entries across ampler capacity shall
 * avoid the overcrowdinge of linked lists, which will allow more direct hash access. */
{
  struct map rehashed_map;
  memcpy(&rehashed_map, map, sizeof(struct map));
  map_create(&rehashed_map);

  /* Temporarily enables the `Map_Flag__Rehashing` which prevents copying the keys
   * and values during the rehash, to avoid double copies. */
  map_flag_enable(&rehashed_map, Map_Flag__Rehashing);
  rehashed_map.capacity <<= 1;
  rehashed_map.probe_limit <<= 1;

  struct map_entry* old_entry = map->entries;

  for (u64 i = 0; i < map->capacity; i++, old_entry++) {
    if (old_entry->key == NULL)
      continue;

    map_set_with_hash(&rehashed_map,
      old_entry->key, old_entry->value, old_entry->hash);
  }

  map_flag_disable(&rehashed_map, Map_Flag__Rehashing);

  free(map->entries);
  memcpy(map, &rehashed_map, sizeof(struct map));
}
