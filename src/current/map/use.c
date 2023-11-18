int64 __map_use (
    struct __map_fp* map_fp,
    void* key,
    uint64 hash,
    enum __map_use_opmode use_opmode
)
/**
 * This function shall set as used the provided *key* in the map.
 *
 * The offset will be retrieved from the map `find` function.
 *
 * The *rehashing* argument is used only for copying key maps, in order to control
 * the duplication of keys: see more below. */
{
  int64 offset = __map_find(map_fp, key, hash, __Map_Find_Offset);

  if (map_fp->usage[offset])
    /* The key is already used, nothing to do. */
    return offset;

  /* Updates usage, hashes and length. */
  map_fp->usage[offset] = true;
  map_fp->hashes[offset] = hash;
  map_fp->length++;

  struct arena* arena = map_fp->config.arena;
  if (map_fp->config.copy_keys)
    goto copied_key;
  else
    goto standard_key;

copied_key:
  void** keys = (void**) map_fp->keys;

  /* If rehashing, this key was already copied in a previous #__map_set.
   * No need to copy it again. */
  if (use_opmode == __Map_Use_Rehashing) {
    keys[offset] = key;
    return offset;
  }

  /* If not rehashing, this key is being seen for the first time in the map.
   * As a quality of life for the developer, it makes a copy of the key so that the
   * map does not depend on the lifetime of outside objects. */
  uint64 (*key_size_func)(void*) = map_fp->config.key_size_func;
  void (*key_copy_func)(void*, void*, uint64) = map_fp->config.key_copy_func;

  uint64 key_length = (key_size_func == NULL)
    ? map_fp->config.key_size_copy
    : key_size_func(key);
  void* key_copy = arena_calloc(arena, 1, key_length);

  if (key_copy_func == NULL)
    memcpy(key_copy, key, key_length);
  else
    key_copy_func(key, key_copy, key_length);

  keys[offset] = key_copy;
  return offset;

standard_key:
  uint64 key_size = map_fp->config.key_size;
  void* key_location = (byte*) map_fp->keys + (offset * key_size);
  memcpy(key_location, key, key_size);
  return offset;
}
