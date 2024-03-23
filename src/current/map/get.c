void* map_get (
    Map* map,
    void* key
)
/**
 * This function shall retrieve the value of the provided *key* in the map.
 *
 * If the key is not present in the map, `NULL` shall be returned. */
{
  MapEntry* entry = map_entry_get(map, key);

  if (entry == NULL)
    return NULL;
  else
    return entry->value;
}
