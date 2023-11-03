/**
 * This function shall set as used the provided *key* in the map.
 *
 * The offset will be retrieved from the map data `find` field, so a map lookup
 * must be done prior to calling this function. */
void __map_use (
    struct __map_data* data,
    void* key,
    bool rehashing
)
{
  uint32 offset = data->find.offset;

  if (data->usage[offset])
    /* The key is already used, nothing to do. */
    return;

  if (data->has_string_key) {
    char** keys = (char**) data->keys;
    if (rehashing) {
      keys[offset] = key;
    } else {
      char* key_copy = strdup(key);
      keys[offset] = key_copy;
    }
  } else {
    uint32 key_size = data->key_size;
    void* key_location = (byte*) data->keys + (offset * key_size);
    memcpy(key_location, key, key_size);
  }

  data->usage[offset] = true;
  data->hashes[offset] = data->find.hash;
  data->length++;
}
