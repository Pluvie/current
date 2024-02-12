void map_entry_key_set (
    struct map* map_ptr,
    struct map_entry* entry,
    void* key
)
/**
 * This function shall set the provided *key* in the provided *entry*.
 *
 * If the map has the copy key flag enabled, then this function shall make a copy of the
 * provided *key* and store that copy in the provided *entry*. */
{
  if (map_ptr->flags & Map_Flag__Copy_Keys)
    goto make_a_copy;

  entry->key = key;
  return;

make_a_copy:
  size key_size = map_ptr->key_size;
  void* key_copy = arena_calloc(map_ptr->arena, 1, key_size);
  memcpy(key_copy, key, key_size);
  entry->key = key_copy;
}