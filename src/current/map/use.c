/**
 * This function shall set as used the provided *key* in the map.
 *
 * The offset will be retrieved from the map data `find` field, so a map lookup
 * must be done prior to calling this function.
 *
 * The *rehashing* argument is used only for string key maps, in order to control
 * the duplication of string keys: see more below. */
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

  /* Updates usage, hashes and length. */
  data->usage[offset] = true;
  data->hashes[offset] = data->find.hash;
  data->length++;

  if (data->has_string_key)
    goto string_key;
  else
    goto standard_key;

string_key:
  char** keys = (char**) data->keys;

  /* If not rehashing, this key is being seen for the first time in the map.
   * As a quality of life for the developer, it makes a copy of the key so that the
   * map does not depend on the lifetime of outside strings. */
  if (!rehashing) {
    char* key_copy = strdup(key);
    keys[offset] = key_copy;
    return;
  }

  /* If rehashing, this key was already copied in a previous #__map_set.
   * No need to copy it again. */
  keys[offset] = key;
  return;

standard_key:
  uint32 key_size = data->key_size;
  void* key_location = (byte*) data->keys + (offset * key_size);
  memcpy(key_location, key, key_size);
  return;
}
