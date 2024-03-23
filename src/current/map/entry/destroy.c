void map_entry_destroy (
    Map* map,
    MapEntry* entry
)
/**
 * This function shall free the provided map *entry*. */
{
  if (entry == NULL)
    return;

  if (map->flags & MAP_FLAG__COPY_KEYS)
    free(entry->key);
  if (map->flags & MAP_FLAG__COPY_VALUES)
    free(entry->value);
}
