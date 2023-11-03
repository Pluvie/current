/**
 * This function shall set as not used the provided *key* in the map, and shall
 * zero-out the corrisponding value.
 *
 * The pos will be retrieved from the map data `find` field, so a map lookup
 * must be done prior to calling this function. */
void __map_delete (
    struct __map_data* data,
    void* key
)
{
  uint32 pos = data->find.pos;
  if (pos == -1) return;

  data->usage[pos] = false;
  data->hashes[pos] = 0;
  data->length--;

  uint32 value_size = data->value_size;
  void* values = (byte*) (data + 1) + value_size;
  void* value_location = (byte*) values + (pos * value_size);
  memset(value_location, '\0', value_size);

  if (data->has_string_key)
    goto string_key;
  else
    goto standard_key;

string_key:
  char** keys = (char**) data->keys;
  free(keys[pos]);
  keys[pos] = NULL;
  return;

standard_key:
  uint32 key_size = data->key_size;
  void* key_location = (byte*) data->keys + (pos * key_size);
  memset(key_location, '\0', key_size);
  return;
}
