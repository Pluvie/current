void map_rehash (
    Map* map
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
  Map rehashed_map;
  memcpy(&rehashed_map, map, sizeof(Map));

  rehashed_map.length = 0;
  rehashed_map.capacity <<= 1;
  rehashed_map.probe_limit <<= 1;

  u32 original_flags = map->flags;
  /* Enables fixed lookup flag: we can assume that the keys are unique, since we just
   * have to redistribute them over a broader capacity. */
  map_flag_enable(&rehashed_map, MAP_FLAG__FIXED_LOOKUP);
  /* Disables the copy flags: we want to avoid double copies, the keys and values of
   * the map are already a copy of the original, so we can keep their addresses. */
  map_flag_disable(&rehashed_map, MAP_FLAG__COPY_KEYS);
  map_flag_disable(&rehashed_map, MAP_FLAG__COPY_VALUES);

  map_create(&rehashed_map);

  MapEntry* old_entry = map->entries;

  for (u64 i = 0; i < map->capacity + map->probe_limit; i++, old_entry++) {
    if (old_entry->key == NULL)
      continue;

    map_entry_set(&rehashed_map, old_entry);
  }

  if (map->arena == NULL)
    free(map->entries);

  memcpy(map, &rehashed_map, sizeof(Map));
  map->flags = original_flags;
}
