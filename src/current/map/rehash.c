/**
 * This function shall extend a map and rehash all its keys.
 *
 * This operation is necessary when the map starts to be overcrowded. In order to
 * avoid performance degradation in key lookups, more space needs to be made, so that
 * hashed values can distribute more evenly across the map.
 *
 * The load threshold of this operation is when the ratio between map length and
 * map capacity reaches `0.7`.
 *
 * The rehash operation will double the capacity of the map and recalculate all
 * keys and values position in the map. The length of the map will of course remain
 * unchanged, as this operation simply redistributes the map data across more space. */
void* __map_rehash (
    void* map_ptr,
    struct __map_data* data
)
{
  uint32 capacity = data->capacity;
  uint32 old_capacity = capacity;
  uint32 key_size = data->key_size;
  uint32 value_size = data->value_size;

  /* Doubles capacity, by simply bit shifting the number left by one. */
  capacity <<= 1;

  /* Keeps the old data reference: it will be needed to copy the values over to the
   * newly allocated memory. */
  struct __map_data* old_data = data;
  void* old_map_ptr = map_ptr;
  void* old_keys = data->keys;
  bool* old_usage = data->usage;
  uint32* old_hashes = data->hashes;

  /* Allocates an entire new map with the doubled capacity. In the map data,
   * the info that will not change are copied over from the old map data. */
  data = calloc(1, map_datasize + value_size + (capacity * value_size));
  data->hash = old_data->hash;
  data->compare = old_data->compare;
  data->key_size = old_data->key_size;
  data->value_size = old_data->value_size;
  data->has_string_key = old_data->has_string_key;
  data->length = 0;
  data->capacity = capacity;
  data->keys = calloc(1, key_size * capacity);
  data->usage = calloc(1, sizeof(bool) * capacity);
  data->hashes = calloc(1, sizeof(uint32) * capacity);
  map_ptr = (byte*) data + map_datasize + value_size;

  void* key = NULL;
  bool used = false;
  uint32 hash = 0;
  int32 offset = -1;

  /* Loops through the old map and redistributes the keys and values. */
  for (uint32 iter = 0; iter < old_capacity; iter++) {
    used = old_usage[iter];
    if (!used) continue;

    /* Reuses the stored hash of the key, so it will not have to be recalculated,
     * speeding up the rehashing a little bit. */
    hash = old_hashes[iter];

    /* Finds the old key and calculates its new offset in the new map. */
    key = (byte*) old_keys + (iter * key_size);
    offset = __map_find(data, key, hash, false);

    /* Sets the key as used in the new map and copies the value at the same
     * offset from the old map to the new map. */
    __map_use(data, key);
    memcpy((byte*) map_ptr + (offset * value_size),
      (byte*) old_map_ptr + (iter * value_size),
      value_size);
  }

  /* Frees the old pointers, everything has been copied over to the new map. */
  free(old_keys);
  free(old_usage);
  free(old_hashes);
  free(old_data);

  /* Returns the fat pointer to the new map. */
  return ((byte*) data + map_datasize + value_size);
}
