void* map_del (
    struct map* map_ptr,
    void* key
)
/**
 * This function shall delete the *provided* key in the map.
 *
 * If the key is found, its value shall be returned.
 * If not, `NULL` shall be returned. */
{
  if (key == NULL)
    return NULL;

  size key_size = map_ptr->key_size;
  u64 hash = map_ptr->hash(key, key_size) % map_ptr->capacity;
  bool (*compare)(void*, void*, size) = map_ptr->compare;
  struct map_entry* entry = map_ptr->buckets[hash];
  struct map_entry* previous_entry = NULL;
  void* deleted_value = NULL;

compare_key:
  if (entry == NULL)
    return NULL;
  if (compare(entry->key, key, key_size)) {
    deleted_value = entry->value;
    goto delete_entry;
  }

  previous_entry = entry;
  entry = entry->next;
  goto compare_key;

delete_entry:
  if (previous_entry == NULL)
    map_ptr->buckets[hash] = entry->next;
  else
    previous_entry->next = entry->next;

  free(entry);
  return deleted_value;
}
