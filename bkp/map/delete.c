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

  void* found_key_address = map_fat_ptr->keys + offset;
  map_fat_ptr->statuses[offset] = __Map__Key_Status__Deleted;
  map_fat_ptr->hashes[offset] = 0;
  map_fat_ptr->length--;
  memset(found_key_address, '\0', map_fat_ptr->config.key_size);

  uint16 value_size = map_fat_ptr->config.value_size;
  void* values = (byte*) (map_fat_ptr + 1) + value_size;
  void* value_location = (byte*) values + (offset * value_size);
  memset(value_location, '\0', value_size);

  return true;
}
