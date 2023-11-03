/**
 * Frees all the memory regions used by a map. */
void __map_free (
    struct __map_data* data
)
{
  if (data->has_string_key) {
    uint32 capacity = data->capacity;
    char** keys = (char**) data->keys;
    for (uint32 index = 0; index < capacity; index++)
      free(keys[index]);
  }

  free(data->keys);
  free(data->usage);
  free(data->hashes);
  free(data);
}
