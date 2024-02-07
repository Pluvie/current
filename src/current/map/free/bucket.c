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

  if (map_ptr->flags & Map_Flag__Copy_Keys)
    free(entry->key);

  free(entry);
}
