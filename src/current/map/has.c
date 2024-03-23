bool map_has (
    Map* map,
    void* key
)
/**
 * This function shall determine if the provided *key* is present in the map.
 *
 * If the key is present in the map, `true` shall be returned.
 * If the key is not present in the map, `false` shall be returned. */
{
  MapEntry* entry = map_entry_get(map, key);

  return entry != NULL;
}
