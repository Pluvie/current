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
  struct arena* arena = map_fp->arena;
  uint64 capacity = map_fp->capacity;
  uint64 old_capacity = capacity;
  uint64 key_size = map_fp->key_size;
  uint64 value_size = map_fp->value_size;
  bool copied_keys = map_fp->copy_keys;

  /* Doubles capacity, by simply bit shifting the number left by one. */
  capacity <<= 1;

  /* Keeps the old map_fp reference: it will be needed to copy the values over to the
   * newly allocated memory. */
  struct __map_fp* old_map_fp = map_fp;
  void* old_map_ptr = map_ptr;
  void* old_keys = map_fp->keys;
  bool* old_usage = map_fp->usage;
  uint64* old_hashes = map_fp->hashes;

  /* Allocates an entire new map with the doubled capacity. In the map map_fp,
   * the info that will not change are copied over from the old map map_fp. */
  map_fp = (arena == NULL)
    ? calloc(1, map_fp_size + value_size + (capacity * value_size))
    : arena_calloc(arena, 1, map_fp_size + value_size + (capacity * value_size));
  memcpy(map_fp, old_map_fp, map_fp_size);
  map_fp->length = 0;
  map_fp->capacity = capacity;
  map_fp->keys = (arena == NULL)
    ? calloc(1, key_size * capacity)
    : arena_calloc(arena, 1, key_size * capacity);
  map_fp->usage = (arena == NULL)
    ? calloc(1, sizeof(bool) * capacity)
    : arena_calloc(arena, 1, sizeof(bool) * capacity);
  map_fp->hashes = (arena == NULL)
    ? calloc(1, sizeof(uint64) * capacity)
    : arena_calloc(arena, 1, sizeof(uint64) * capacity);
  map_ptr = (byte*) map_fp + map_fp_size + value_size;

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

    /* Finds the old key, calculates its new offset in the new map, and sets the
     * key as used. */
    key = (copied_keys)
      ? ((void**) old_keys)[iter]
      : (byte*) old_keys + (iter * key_size);
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
  return ((byte*) map_fp + map_fp_size + value_size);
}
