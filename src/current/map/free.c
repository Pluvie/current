void map_free (
    struct map* map
)
/**
 * This function shall free the memory used by the map and all its buckets. */
{
  if (map->arena != NULL)
    return;

  for (i64 i = 0; i < map->capacity; i++)
    map_free_bucket(map, map->buckets[i]);
  free(map->buckets);
}
