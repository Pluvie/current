struct map_entry* map_add_entry (
    struct map* map_ptr,
    void* key,
    void* value
)
{
  struct map_entry* entry = calloc(1, sizeof(struct map_entry));
  entry->key = key;
  entry->value = value;
  map_ptr->length++;
  return entry;
}
