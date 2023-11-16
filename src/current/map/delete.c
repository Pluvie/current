void __map_delete (
    struct __map_fp* map_fp,
    void* key,
    uint64 hash
)
/**
 * This function shall set as not used the provided *key* in the map, and shall
 * zero-out the corrisponding value. */
{
  int64 pos = __map_find(map_fp, key, hash, __Map_Find_Pos);
  if (pos == -1) return;

  struct arena* arena = map_fp->arena;
  map_fp->usage[pos] = false;
  map_fp->hashes[pos] = 0;
  map_fp->length--;

  uint64 value_size = map_fp->value_size;
  void* values = (byte*) (map_fp + 1) + value_size;
  void* value_location = (byte*) values + (pos * value_size);
  memset(value_location, '\0', value_size);

  if (map_fp->copy_keys)
    goto copied_key;
  else
    goto standard_key;

copied_key:
  void** keys = (void**) map_fp->keys;
  if (arena == NULL)
    free(keys[pos]);
  keys[pos] = NULL;
  return;

standard_key:
  uint64 key_size = map_fp->key_size;
  void* key_location = (byte*) map_fp->keys + (pos * key_size);
  memset(key_location, '\0', key_size);
  return;
}
