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

  rehashed_map.capacity <<= 1;
  rehashed_map.probe_limit <<= 1;

  struct map_entry* old_entry = map->entries;

  for (u64 i = 0; i < map->capacity; i++, old_entry++) {
    if (old_entry->key == NULL)
      continue;

    map_set_entry(&rehashed_map, old_entry);
  }

  free(map->entries);
  memcpy(map, &rehashed_map, sizeof(struct map));
}
