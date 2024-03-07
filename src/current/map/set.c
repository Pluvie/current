void* map_set (
    struct map* map,
    void* key,
    void* value
)
/**
 * This function shall set corresponding *key* with the provided *value* in the
 * map entries.
 *
 * If the *key* is already present in the entries, its value shall be replaced,
 * otherwise a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  if (key == NULL)
    return NULL;

  u64 hash = map_hash(key, map->key_size);
  struct map_entry entry = { .key = key, .value = value, .hash = hash };

check_key_copy:
  if (!(map->flags & Map_Flag__Copy_Keys))
    goto check_value_copy;

  size key_size = map->key_size;
  void* key_copy = arena_calloc(map->arena, 1, key_size);
  memcpy(key_copy, key, key_size);
  entry.key = key_copy;

check_value_copy:
  if (!(map->flags & Map_Flag__Copy_Values))
    goto set_entry;

  size value_size = map->value_size;
  void* value_copy = arena_calloc(map->arena, 1, value_size);
  memcpy(value_copy, value, value_size);
  entry.value = value_copy;

set_entry:
  return map_set_entry(map, &entry);
}
