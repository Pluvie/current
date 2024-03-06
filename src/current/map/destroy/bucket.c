void map_destroy_bucket (
    struct map* map,
    struct map_entry* entry
)
/**
 * This function shall recursively free all entries in a bucket. */
{
  if (entry == NULL)
    return;

  map_destroy_bucket(map, entry->next);
  map_destroy_entry(map, entry);
}
