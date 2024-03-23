void* map_del (
    Map* map,
    void* key
)
/**
 * This function shall delete the *provided* key in the map.
 *
 * If the key is found, its value shall be returned.
 * If not, `NULL` shall be returned. */
{
  MapEntry* entry = map_entry_get(map, key);

  if (entry == NULL)
    return NULL;

  void* deleted_value = entry->value;
  map_entry_destroy(map, entry);
  memset(entry, '\0', sizeof(MapEntry));

  return deleted_value;
}
