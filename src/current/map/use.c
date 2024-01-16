int64 __map_use (
    void* key_address,
    uint64 key_hash,
    struct __map_fat_ptr* map_fat_ptr,
    enum __map_use_opmode use_opmode
)
/**
 * This function shall set as used a key in the map, using the provided *key_address*
 * and *key_hash*.
 *
 * The *key_hash* has to be calculated in advance as an optimization to speed up the
 * rehash function, because Current map implementation already stores all the hashed
 * values of the keys.
 *
 * The offset will be retrieved from the map `find` function.
 *
 * The *rehashing* argument is used only for copying key maps, in order to control
 * the duplication of keys: see more below. */
{
  int64 offset = __map_find(key_address, key_hash, map_fat_ptr, __Map_Find_Offset);

  if (offset < 0)
    /* Key not found, nothing to do. */
    return offset;

  struct __map_key* key = map_fat_ptr->keys + offset;

  if (key->status == __Map__Key_Status__Used)
    /* The key is already used, nothing to do. */
    return offset;

  /* Updates key status, key hash and map length. */
  key->status = __Map__Key_Status__Used;
  key->hash = key_hash;
  map_fat_ptr->length++;

  if (map_fat_ptr->config.copy_keys)
    goto copy_key;
  else
    goto set_key;

copy_key:
  /* If rehashing, this key was already copied in a previous #__map_set.
   * No need to copy it again. */
  if (use_opmode == __Map_Use_Rehashing)
    goto set_key;

  /* If not rehashing, this key is being seen for the first time in the map.
   * As a quality of life for the developer, it makes a copy of the key so that the
   * map does not depend on the lifetime of outside objects. */
  struct arena* arena = map_fat_ptr->config.arena;
  uint16 (*key_copy_size_func)(void*) = map_fat_ptr->config.key_copy_size_func;
  void (*key_copy_func)(void*, void*, uint64) = map_fat_ptr->config.key_copy_func;
  uint16 key_size = (key_copy_size_func == NULL)
    ? map_fat_ptr->config.key_copy_size
    : key_copy_size_func(key);
  void* key_copy_address = arena_calloc(arena, 1, key_size);

  if (key_copy_func == NULL)
    memcpy(key_copy_address, key_address, key_size);
  else
    key_copy_func(key_copy_address, key_address, key_size);

  key->address = key_copy_address;
  return offset;

set_key:
  key->address = key_address;
  return offset;
}
