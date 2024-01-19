void map_free_bucket (
    struct map_entry* entry
)
/**
 * This function shall recursively free all entries in a bucket. */
{
  if (entry == NULL) return;
  map_free_bucket(entry->next);
  free(entry);
}
