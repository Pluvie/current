void map_pretty_print (
    struct map* map_ptr
)
{
  for (u64 i = 0; i < map_ptr->capacity; i++)
    map_pretty_print_bucket(
      map_ptr->key_size, map_ptr->value_size, i, map_ptr->buckets[i]);
}
