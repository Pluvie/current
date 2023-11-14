int64 __map_use (
    struct __map_fp* map_fp,
    void* key,
    uint64 hash,
    enum __map_use_op use_op
)
/**
 * This function shall set as used the provided *key* in the map.
 *
 * The offset will be retrieved from the map `find` function.
 *
 * The *rehashing* argument is used only for copying key maps, in order to control
 * the duplication of keys: see more below. */
{
  arena* allocator = map_fp->allocator;
  int64 offset = __map_find(map_fp, key, hash, __Map_Find_Offset);

  if (map_fp->usage[offset])
    /* The key is already used, nothing to do. */
    return offset;

  /* Updates usage, hashes and length. */
  map_fp->usage[offset] = true;
  map_fp->hashes[offset] = hash;
  map_fp->length++;

  if (map_fp->copy_keys)
    goto copied_key;
  else
    goto standard_key;

copied_key:
  void** keys = (void**) map_fp->keys;

  /* If not rehashing, this key is being seen for the first time in the map.
   * As a quality of life for the developer, it makes a copy of the key so that the
   * map does not depend on the lifetime of outside objects. */
  if (use_op != __Map_Use_Rehashing) {
    uint64 key_length = map_fp->key_length(key);
    void* key_copy = (allocator == NULL)
      ? calloc(1, key_length)
      : arena_calloc(allocator, 1, key_length);
    map_fp->key_copy(key, key_copy, key_length);
    keys[offset] = key_copy;
    return offset;
  }

  /* If rehashing, this key was already copied in a previous #__map_set.
   * No need to copy it again. */
  keys[offset] = key;
  return offset;

standard_key:
  uint64 key_size = map_fp->key_size;
  void* key_location = (byte*) map_fp->keys + (offset * key_size);
  memcpy(key_location, key, key_size);
  return offset;
}
