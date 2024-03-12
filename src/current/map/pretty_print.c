void map_pretty_print (
    struct map* map
)
/**
 * This function shall pretty print the map, showing all entries of the map.
 *
 * For each entry, this function shall print the bytes of its key and value. */
{
  struct map_entry* entry = map->entries;
  for (u64 i = 0; i < map->capacity + map->probe_limit; i++, entry++)
    map_pretty_print_entry(map->key_size, map->value_size, i, entry);
}
