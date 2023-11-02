/**
 * Frees all the memory regions used by a map. */
void __map_free (
    struct __map_data* data
)
{
  free(data->keys);
  free(data->usage);
  free(data->hashes);
  free(data);
}
