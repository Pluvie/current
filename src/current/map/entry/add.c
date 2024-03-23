inline void* map_entry_add (
    Map* map,
    MapEntry* entry,
    MapEntry* location
)
/**
 * This function shall add a new *entry* in the map, at the provided *location*.
 *
 * If, after adding the new entry, the map load reaches or surpasses the
 * `MAP_MAXIMUM_LOAD_FACTOR` threshold, then this function shall trigger a rehash,
 * invoking the #map_rehash function. */
{
check_key_copy:
  if (!(map->flags & MAP_FLAG__COPY_KEYS))
    goto check_value_copy;

  size key_size = map->key_size;
  void* key_copy = arena_calloc(map->arena, 1, key_size);
  memcpy(key_copy, entry->key, key_size);
  entry->key = key_copy;

check_value_copy:
  if (!(map->flags & MAP_FLAG__COPY_VALUES))
    goto add_entry;

  size value_size = map->value_size;
  void* value_copy = arena_calloc(map->arena, 1, value_size);
  memcpy(value_copy, entry->value, value_size);
  entry->value = value_copy;

add_entry:
  memcpy(location, entry, sizeof(MapEntry));
  map->length++;

check_rehash:
  d64 map_load = (d64) map->length / (d64) map->capacity;
  if (map_load >= MAP_MAXIMUM_LOAD_FACTOR)
    map_rehash(map);

  return entry->value;
}
