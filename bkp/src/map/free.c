void __map_free (
    struct __map_fat_ptr* map_fat_ptr
)
/**
 * Frees all the memory regions used by a map. */
{
  if (map_fat_ptr->config.arena != NULL)
    return;

  if (map_fat_ptr->config.copy_keys) {
    uint32 capacity = map_fat_ptr->capacity;
    void** keys = (void**) map_fat_ptr->keys;
    for (uint64 index = 0; index < capacity; index++)
      free(keys[index]);
  }

  free(map_fat_ptr->keys);
  free(map_fat_ptr->hashes);
  free(map_fat_ptr->statuses);
  free(map_fat_ptr);
}
