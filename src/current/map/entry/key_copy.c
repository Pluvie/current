void map_entry_key_copy (
    struct map* map_ptr,
    struct map_entry* entry,
    void* key
)
/**
 * This function shall make a copy of the provided *key* and store that copy in the
 * provided *entry*. */
{
  size key_size = map_ptr->key_size;
  void* key_copy = arena_calloc(map_ptr->arena, 1, key_size);
  memcpy(key_copy, key, key_size);
  entry->key = key_copy;
}
