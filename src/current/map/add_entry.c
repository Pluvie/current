void map_add_entry (
    struct map* map_ptr,
    void* key,
    void* value,
    struct map_entry** add_location
)
{
  struct map_entry* entry = calloc(1, sizeof(struct map_entry));
  entry->key = key;
  entry->value = value;
  *add_location = entry;

  map_ptr->length++;
  if (((d64) map_ptr->length / (d64) map_ptr->capacity) >= 0.7)
    map_rehash(map_ptr);
}
