void map_entry_key_set (
    struct map* map,
    struct map_entry* entry,
    void* key
)
/**
 * This function shall set the provided *key* in the provided *entry*.
 *
 * If the map has the copy key flag enabled, then this function shall make a copy of the
 * provided *key* and store that copy in the provided *entry*. */
{
  if (map->flags & Map_Flag__Rehashing)
    goto do_not_copy;

  if (map->flags & Map_Flag__Copy_Keys)
    goto do_copy;

do_not_copy:
  entry->key = key;
  return;

do_copy:
  size key_size = map->key_size;
  void* key_copy = arena_calloc(map->arena, 1, key_size);
  memcpy(key_copy, key, key_size);
  entry->key = key_copy;
  return;
}
