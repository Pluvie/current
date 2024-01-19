void map_rehash (
    struct map* map_ptr
)
/**
 * This function shall double the map capacity and shall reposition all entries in their
 * new hashed location in the buckets.
 *
 * This operation is necessary in order to avoid overcrowding of the map: when this
 * happens, the map performances start to degrade, because the buckets will hold more
 * and more entries in the linked lists, requiring linear search in order to find
 * the entries.
 *
 * Increasing the capacity and redistributing the entries across ampler buckets shall
 * avoid the overcrowdinge of linked lists, which will allow more direct hash access. */
{
  u64 old_capacity = map_ptr->capacity;
  u64 new_capacity = old_capacity * 2;

  map_ptr->length = 0;
  map_ptr->capacity = new_capacity;
  struct map_entry* old_entry = NULL;
  struct map_entry** new_buckets = calloc(new_capacity, sizeof(struct map_entry*));

  u64 index = 0;
  old_entry = map_ptr->buckets[index];
next_entry:
  if (old_entry == NULL)
    goto next_bucket;

  map_set_on_buckets(
    map_ptr, old_entry->key, old_entry->value, old_entry->hash, new_buckets);

  if (old_entry->next == NULL)
    goto next_bucket;

  old_entry = old_entry->next;
  goto next_entry;

next_bucket:
  map_free_bucket(map_ptr->buckets[index]);
  index++;
  if (index >= old_capacity)
    goto assign_new_buckets;

  old_entry = map_ptr->buckets[index];
  goto next_entry;

assign_new_buckets:
  free(map_ptr->buckets);
  map_ptr->buckets = new_buckets;
}
