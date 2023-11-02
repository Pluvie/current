/**
 * This function shall set as used the provided *key* in the map.
 *
 * The offset will be retrieved from the map data `find` field, so a map lookup
 * must be done prior to calling this function. */
void __map_use (
    struct __map_data* data,
    void* key
)
{
  uint32 offset = data->find.offset;
  uint32 key_size = data->key_size;

  void* key_location = (byte*) data->keys + (offset * key_size);
  memcpy(key_location, key, key_size);

  bool already_used = data->usage[offset];
  if (already_used) return;
  data->usage[offset] = true;
  data->hashes[offset] = data->find.hash;
  data->length++;
}
