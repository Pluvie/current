void map_pretty_print (
    struct map* map_ptr
)
/**
 * This function shall pretty print the map, showing all entries in the map grouped
 * in buckets.
 *
 * For each entry, this function shall print the bytes of its key and value. */
{
  for (u64 i = 0; i < map_ptr->capacity; i++)
    map_pretty_print_bucket(
      map_ptr->key_size, map_ptr->value_size, i, map_ptr->buckets[i]);
}
