void* map_set_on_buckets (
    struct map* map_ptr,
    void* key,
    void* value,
    u64 hash,
    struct map_entry** buckets
)
/**
 * This function shall set corresponding *key* with the provided *value* in the
 * provided *buckets*, using the precalculated *hash*.
 *
 * If the *key* is already present in the buckets, its value shall be replaced,
 * otherwise a new entry shall be added.
 *
 * The function will return the provided *value*. */
{
  if (key == NULL)
    return NULL;

  u64 capped_hash = hash % map_ptr->capacity;
  size key_size = map_ptr->key_size;
  struct map_entry* entry = buckets[capped_hash];
  if (entry != NULL)
    goto search_entry;

  map_add_entry(map_ptr, key, value, hash, buckets + capped_hash);
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
  map_add_entry(map_ptr, key, value, hash, &(entry->next));
  return value;
}
