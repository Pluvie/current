void map_rehash (
    struct map* map
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
  u64 old_capacity = map->capacity;
  u64 new_capacity = old_capacity * 2;

  map->length = 0;
  map->capacity = new_capacity;
  struct map_entry* old_entry = NULL;
  struct map_entry** new_buckets = calloc(new_capacity, sizeof(struct map_entry*));

  /* Temporarily enables the `Map_Flag__Rehashing` which prevents copying the keys
   * and values during the rehash, to avoid double copies. */
  map_flag_enable(map, Map_Flag__Rehashing);

  u64 index = 0;
  old_entry = map->buckets[index];
  /* Starting from the first entry of the first bucket, the following cycle will pass
   * over every entry in the map, and will set its corresponding key and value in the
   * new buckets, thus effectively redistributing the load. */

next_entry:
  if (old_entry == NULL)
    goto next_bucket;

  map_set_with_buckets(
    map, old_entry->key, old_entry->value, old_entry->hash, new_buckets);

  if (old_entry->next == NULL)
    goto next_bucket;

  old_entry = old_entry->next;
  goto next_entry;

next_bucket:
  map_destroy_bucket(map, map->buckets[index]);
  index++;
  if (index >= old_capacity)
    goto assign_new_buckets;

  old_entry = map->buckets[index];
  goto next_entry;

assign_new_buckets:
  free(map->buckets);
  map->buckets = new_buckets;
  map_flag_disable(map, Map_Flag__Rehashing);
}
