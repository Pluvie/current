void map_add_entry (
    struct map* map_ptr,
    void* key,
    void* value,
    u64 hash,
    struct map_entry** add_location
)
/**
 * This function shall add a new entry in the map, with the provided *key*, *value* and
 * *hash*.
 *
 * The entry will be stored at the provided *add_location*, which must be an entry
 * pointer address. In other words, the caller of this function must know in advance
 * where the new entry must be added: this function will not do any reasoning in this
 * matter.
 *
 * If, after adding the new entry, the map load reaches or surpasses the
 * `MAP_MAXIMUM_LOAD_FACTOR` threshold, then this function shall trigger a rehash,
 * invoking the #map_rehash function. */
{
  struct map_entry* entry = calloc(1, sizeof(struct map_entry));
  entry->key = key;
  entry->value = value;
  entry->hash = hash;
  *add_location = entry;

  map_ptr->length++;
  if (((d64) map_ptr->length / (d64) map_ptr->capacity) >= MAP_MAXIMUM_LOAD_FACTOR)
    map_rehash(map_ptr);
}
