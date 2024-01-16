bool __map_delete (
    void* key_address,
    uint64 key_hash,
    struct __map_fat_ptr* map_fat_ptr
)
/**
 * This function shall set as deleted a key in the map, and shall zero-out the
 * corrisponding value.
 *
 * The offset will be retrieved from the map `find` function.
 *
 * Returns true if the key was found and successfully deleted, false otherwise. */
{
  int64 offset = __map_find(key_address, key_hash, map_fat_ptr, __Map_Find_Default);
  if (offset < 0)
    /* Key not found, nothing to do. */
    return false;

  struct __map_key* key = map_fat_ptr->keys + offset;
  key->status = __Map__Key_Status__Deleted;
  key->hash = 0;
  key->address = NULL;

  uint16 value_size = map_fat_ptr->config.value_size;
  void* values = (byte*) (map_fat_ptr + 1) + value_size;
  void* value_location = (byte*) values + (offset * value_size);
  memset(value_location, '\0', value_size);

  return true;
}
