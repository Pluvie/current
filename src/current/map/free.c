void __map_free (
    struct __map_fp* map_fp
)
/**
 * Frees all the memory regions used by a map. */
{
  if (map_fp->allocator != NULL)
    return;

  if (map_fp->copy_keys) {
    uint32 capacity = map_fp->capacity;
    void** keys = (void**) map_fp->keys;
    for (uint64 index = 0; index < capacity; index++)
      free(keys[index]);
  }

  free(map_fp->keys);
  free(map_fp->usage);
  free(map_fp->hashes);
  free(map_fp);
}
