void map_free (
    struct map* map_ptr
)
{
  for (i64 i = 0; i < map_ptr->capacity; i++)
    map_free_bucket(map_ptr->buckets[i]);
  free(map_ptr->buckets);
  free(map_ptr);
}
