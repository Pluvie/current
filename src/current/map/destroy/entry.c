void map_destroy_entry (
    struct map* map,
    struct map_entry* entry
)
/**
 * This function shall recursively free all entries in a bucket. */
{
  if (entry == NULL)
    return;

  /* If rehashing, do not ever free the entry key and value, even if the copy flags are
   * enabled. They will be reused. */
  if (map->flags & Map_Flag__Rehashing)
    goto free_entry;

  if (map->flags & Map_Flag__Copy_Keys)
    free(entry->key);
  if (map->flags & Map_Flag__Copy_Values)
    free(entry->value);

free_entry:
  free(entry);
}
