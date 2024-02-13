void map_free_bucket (
    struct map* map_ptr,
    struct map_entry* entry
)
/**
 * This function shall recursively free all entries in a bucket. */
{
  if (entry == NULL)
    return;

  map_free_bucket(map_ptr, entry->next);
  map_free_entry(map_ptr, entry);
}
