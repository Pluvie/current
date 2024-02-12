void map_entry_value_set (
    struct map* map_ptr,
    struct map_entry* entry,
    void* value
)
/**
 * This function shall set the provided *value* in the provided *entry*.
 *
 * If the map has the copy value flag enabled, then this function shall make a copy of the
 * provided *value* and store that copy in the provided *entry*. */
{
  if (map_ptr->flags & Map_Flag__Copy_Values)
    goto make_a_copy;

  entry->value = value;
  return;

make_a_copy:
  if (map_ptr->arena == NULL)
    free(entry->value);

  size value_size = map_ptr->value_size;
  void* value_copy = arena_calloc(map_ptr->arena, 1, value_size);
  memcpy(value_copy, value, value_size);
  entry->value = value_copy;
}
