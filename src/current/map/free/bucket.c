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

  /* If rehashing, do not ever free the entry key and value, even if the copy flags are
   * enabled. They will be reused. */
  if (map_ptr->flags & Map_Flag__Rehashing)
    goto free_entry;

  if (map_ptr->flags & Map_Flag__Copy_Keys)
    free(entry->key);
  if (map_ptr->flags & Map_Flag__Copy_Values)
    free(entry->value);

free_entry:
  free(entry);
}
