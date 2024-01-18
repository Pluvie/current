void map_free_bucket (
    struct map_entry* entry
)
{
  if (entry == NULL) return;
  map_free_bucket(entry->next);
  free(entry);
}
