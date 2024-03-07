void map_destroy (
    struct map* map
)
/**
 * This function shall free the memory used by the map and all its entries. */
{
  if (map->arena != NULL)
    return;

  for (i64 i = 0; i < map->capacity; i++)
    map_destroy_entry(map, map->entries + i);
  free(map->entries);
}