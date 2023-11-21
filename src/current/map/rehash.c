void* __map_rehash (
    void* map_ptr,
    struct __map_fp* map_fp
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
  struct arena* arena = map_fp->config.arena;
  uint64 old_capacity = map_fp->capacity;
  uint64 key_size = map_fp->config.key_size;
  uint64 value_size = map_fp->config.value_size;

  /* Keeps the old map_fp reference: it will be needed to copy the values over to the
   * newly allocated memory. */
  struct __map_fp* old_map_fp = map_fp;
  void* old_map_ptr = map_ptr;
  void* old_keys = map_fp->keys;
  bool* old_usage = map_fp->usage;
  uint64* old_hashes = map_fp->hashes;

  /* Allocates an entire new map with the doubled capacity. In the map map_fp,
   * the info that will not change are copied over from the old map map_fp. */
  struct __map_memsize memsize = __map_calc_memsize(key_size, value_size, old_capacity);
  uint64 capacity = memsize.capacity;
  //uint64 footprint = memsize.footprint;
  //arena_prealloc(arena, footprint);

  map_fp = arena_calloc(arena, 1,
    sizeof(struct __map_fp) +
    value_size +
    (capacity * value_size));
  memcpy(map_fp, old_map_fp, sizeof(struct __map_fp));
  map_fp->length = 0;
  map_fp->capacity = capacity;
  map_fp->keys = arena_calloc(arena, capacity, key_size);
  map_fp->usage = arena_calloc(arena, capacity, sizeof(bool));
  map_fp->hashes = arena_calloc(arena, capacity, sizeof(uint64));
  map_ptr = (byte*) map_fp + sizeof(struct __map_fp) + value_size;

  void* key = NULL;
  uint64 hash = 0;
  int32 offset = -1;

  /* Loops through the old map and redistributes the keys and values. */
  for (uint64 iter = 0; iter < old_capacity; iter++) {
    /* The key was not used, it will be skipped. */
    if (!old_usage[iter]) continue;

    /* Reuses the stored hash of the key, so it will not have to be recalculated,
     * speeding up the rehashing a little bit. */
    hash = old_hashes[iter];

    /* Calculates the offset of the key in the new map, and sets it as used. */
    key = (byte*) old_keys + (iter * key_size);
    offset = __map_use(map_fp, key, hash, __Map_Use_Rehashing);

    /* Copies the value at the same offset from the old map to the new map. */
    memcpy((byte*) map_ptr + (offset * value_size),
      (byte*) old_map_ptr + (iter * value_size),
      value_size);
  }

  /* Frees the old pointers, everything has been copied over to the new map. */
  if (arena == NULL) {
    free(old_keys);
    free(old_usage);
    free(old_hashes);
    free(old_map_fp);
  }

  /* Returns the fat pointer to the new map. */
  return ((byte*) map_fp + sizeof(struct __map_fp) + value_size);
}
