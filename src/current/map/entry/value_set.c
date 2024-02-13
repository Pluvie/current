void map_entry_value_set (
    struct map* map_ptr,
    struct map_entry* entry,
    void* value
)
/**
 * This function shall set the provided *value* in the provided *entry*.
 *
 * If the map has the copy value flag enabled, then this function shall make a copy of
 * the provided *value* and store that copy in the provided *entry*. */
{
  if (map_ptr->flags & Map_Flag__Rehashing)
    goto do_not_copy;

  if (map_ptr->flags & Map_Flag__Copy_Values)
    goto do_copy;

do_not_copy:
  entry->value = value;
  return;

do_copy:
  size value_size = map_ptr->value_size;

  /* The entry *value* is not `NULL`, therefore it was already copied in a previous
   * call of #map_entry_value_set. Even if the `Map_Flag__Copy_Values` is enabled, we
   * avoid doing another copy -- which is redundant -- and instead reuse the already
   * allocated memory, overwriting it with the new value. */
  if (entry->value != NULL)
    goto reuse_memory;

  void* value_copy = arena_calloc(map_ptr->arena, 1, value_size);
  memcpy(value_copy, value, value_size);
  entry->value = value_copy;
  return;

reuse_memory:
  memcpy(entry->value, value, value_size);
  return;
}
