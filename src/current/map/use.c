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

  bool already_used = data->usage[offset];
  if (already_used) return;

  uint32 key_size = data->key_size;
  void* key_location = (byte*) data->keys + (offset * key_size);
  if (data->has_string_key) {
    char* key_copy = strdup(*(char**) key);
    memcpy(key_location, &key_copy, sizeof(char*));
  } else {
    memcpy(key_location, key, key_size);
  }

  data->usage[offset] = true;
  data->hashes[offset] = data->find.hash;
  data->length++;
}
