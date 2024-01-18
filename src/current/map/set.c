bool map_set (
    struct map* map_ptr,
    void* key,
    void* value
)
{
  size key_size = map_ptr->key_size;
  u64 hash = map_ptr->hash(key, key_size) % map_ptr->capacity;
  struct map_entry* entry = map_ptr->buckets[hash];
  if (entry != NULL)
    goto search_entry;

  map_ptr->buckets[hash] = map_add_entry(map_ptr, key, value);
  return true;

search_entry:
  bool (*compare)(void*, void*, size) = map_ptr->compare;

compare_key:
  if (compare(entry->key, key, key_size)) {
    entry->value = value;
    return false;
  }

  if (entry->next == NULL)
    goto append_entry;

  entry = entry->next;
  goto compare_key;

append_entry:
  entry->next = map_add_entry(map_ptr, key, value);
  return true;
}
