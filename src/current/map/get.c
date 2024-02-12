void* map_get (
    struct map* map_ptr,
    void* key
)
/**
 * This function shall retrieve the value of the provided *key* in the map.
 *
 * If the key is not present in the map, `NULL` shall be returned. */
{
  struct map_entry* entry = map_get_entry(map_ptr, key);

  if (entry == NULL)
    return NULL;
  else
    return entry->value;
}
