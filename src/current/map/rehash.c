void* __map_rehash (
    void* map_ptr,
    struct __map_fat_ptr* map_fat_ptr
)
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
{
  struct arena* arena = map_fat_ptr->config.arena;
  uint64 old_capacity = map_fat_ptr->capacity;
  uint64 key_size = map_fat_ptr->config.key_size;
  uint64 value_size = map_fat_ptr->config.value_size;

  /* Keeps the old map_fat_ptr reference: it will be needed to copy the values over to the
   * newly allocated memory. */
  struct __map_fat_ptr* old_map_fat_ptr = map_fat_ptr;
  void* old_map_ptr = map_ptr;
  void* old_keys = map_fat_ptr->keys;
  uint64* old_hashes = map_fat_ptr->hashes;
  enum __map_key_status* old_statuses = map_fat_ptr->statuses;

  /* Allocates an entire new map with the doubled capacity. In the map map_fat_ptr,
   * the info that will not change are copied over from the old map map_fat_ptr. */
  struct __map_memsize memsize = __map_calc_memsize(key_size, value_size, old_capacity);
  uint64 capacity = memsize.capacity;
  uint64 footprint = memsize.footprint;
  if (arena != NULL)
    arena_prealloc(arena, footprint);

  map_fat_ptr = arena_calloc(arena, 1,
    sizeof(struct __map_fat_ptr) +
    value_size +
    (capacity * value_size));
  memcpy(map_fat_ptr, old_map_fat_ptr, sizeof(struct __map_fat_ptr));
  map_fat_ptr->length = 0;
  map_fat_ptr->capacity = capacity;
  map_fat_ptr->keys = arena_calloc(arena, capacity, key_size);
  map_fat_ptr->hashes = arena_calloc(arena, capacity, sizeof(uint64));
  map_fat_ptr->statuses = arena_calloc(arena, capacity, sizeof(enum __map_key_status));
  map_ptr = (byte*) map_fat_ptr + sizeof(struct __map_fat_ptr) + value_size;

  uint64 hash = 0;
  int32 offset = -1;
  void* key_address = NULL;

  /* Loops through the old map and redistributes the keys and values. */
  for (uint64 iter = 0; iter < old_capacity; iter++) {
    /* The key was not used, it will be skipped. */
    if (!old_statuses[iter]) continue;

    /* Reuses the stored hash of the key, so it will not have to be recalculated,
     * speeding up the rehashing a little bit. */
    hash = old_hashes[iter];

    /* Calculates the offset of the key in the new map, and sets it as used. */
    key_address = (byte*) old_keys + (iter * key_size);
    offset = __map_use(key_address, hash, map_fat_ptr, __Map_Use_Rehashing);

    /* Copies the value at the same offset from the old map to the new map. */
    memcpy((byte*) map_ptr + (offset * value_size),
      (byte*) old_map_ptr + (iter * value_size),
      value_size);
  }

  /* Frees the old pointers, everything has been copied over to the new map. */
  if (arena == NULL) {
    free(old_keys);
    free(old_statuses);
    free(old_hashes);
    free(old_map_fat_ptr);
  }

  /* Returns the fat pointer to the new map. */
  return ((byte*) map_fat_ptr + sizeof(struct __map_fat_ptr) + value_size);
}
