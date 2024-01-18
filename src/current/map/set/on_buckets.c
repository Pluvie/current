void* map_set_on_buckets (
    struct map* map_ptr,
    void* key,
    void* value,
    u64 hash,
    struct map_entry** buckets
)
{
  size key_size = map_ptr->key_size;
  struct map_entry* entry = buckets[hash];
  if (entry != NULL)
    goto search_entry;

  map_add_entry(map_ptr, key, value, buckets + hash);
  return value;

search_entry:
  bool (*compare)(void*, void*, size) = map_ptr->compare;

compare_key:
  if (compare(entry->key, key, key_size)) {
    entry->value = value;
    return value;
  }

  if (entry->next == NULL)
    goto append_entry;

  entry = entry->next;
  goto compare_key;

append_entry:
  map_add_entry(map_ptr, key, value, &(entry->next));
  return value;
}
