bool __map_delete (
    struct __map_fp* map_fp,
    void* key,
    uint64 hash
)
/**
 * This function shall set as deleted the status of the provided *key* in the map, and
 * shall zero-out the corrisponding key and value.
 *
 * The offset will be retrieved from the map `find` function.
 *
 * Returns true if the key was found and successfully deleted, false otherwise. */
{
  int64 offset = __map_find(map_fp, key, hash, __Map_Find_Default);
  if (offset < 0)
    /* Key not found, nothing to do. */
    return false;

  map_fp->statuses[offset] = __Map__Key_Status__Deleted;
  map_fp->hashes[offset] = 0;

  uint64 key_size = map_fp->config.key_size;
  void* key_location = (byte*) map_fp->keys + (offset * key_size);
  memset(key_location, '\0', key_size);

  uint64 value_size = map_fp->config.value_size;
  void* values = (byte*) (map_fp + 1) + value_size;
  void* value_location = (byte*) values + (offset * value_size);
  memset(value_location, '\0', value_size);

  return true;
}
