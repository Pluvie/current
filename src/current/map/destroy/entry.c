void map_destroy_entry (
    struct map* map,
    struct map_entry* entry
)
/**
 * This function shall free the provided map *entry*. */
{
  if (entry == NULL)
    return;

  if (map->flags & Map_Flag__Copy_Keys)
    free(entry->key);
  if (map->flags & Map_Flag__Copy_Values)
    free(entry->value);
}
