bool map_has (
    struct map* map,
    void* key
)
/**
 * This function shall determine if the provided *key* is present in the map.
 *
 * If the key is present in the map, `true` shall be returned.
 * If the key is not present in the map, `false` shall be returned. */
{
  struct map_entry* entry = map_get_entry(map, key);

  return entry != NULL;
}
