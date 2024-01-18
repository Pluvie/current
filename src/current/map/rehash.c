void map_rehash (
    struct map* map_ptr
)
{
  u64 old_capacity = map_ptr->capacity;
  u64 new_capacity = next_pow2(old_capacity);

  map_ptr->capacity = new_capacity;
  struct map_entry* old_entry = NULL;
  struct map_entry* old_bucket = NULL;
  struct map_entry** new_buckets = calloc(new_capacity, sizeof(struct map_entry*));

  u64 index = 0;
  u64 new_hash = 0;
  size key_size = map_ptr->key_size;

  old_entry = map_ptr->buckets[index];
next_entry:
  if (old_entry == NULL) goto next_bucket;
  new_hash = old_entry->hash % new_capacity;
  map_set_on_buckets(map_ptr, old_entry->key, old_entry->value, new_hash, new_buckets);

  if (old_entry->next == NULL) goto next_bucket;
  old_entry = old_entry->next;
  goto next_entry;

next_bucket:
  index++;
  if (index >= old_capacity) goto assign_new_buckets;
  old_entry = map_ptr->buckets[index];
  goto next_entry;

assign_new_buckets:
  map_ptr->buckets = new_buckets;
}
