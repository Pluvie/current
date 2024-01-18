int64 __map_get_key_offset (
    void* key_address,
    uint64 key_hash,
    struct __map_fat_ptr* map_fat_ptr,
    enum __map_find_output find_output
)
/**
 * This function shall get the offset of a key in the map, using the provided
 * *key_address* and *key_hash*.
 *
 * The *key_hash* has to be calculated in advance as an optimization to speed up the
 * rehash function, because Current map implementation already stores all the hashed
 * values of the keys.
 *
 * The argument *find_output* tweaks the returned value of this function, depending
 * on whether the key is found in the map. These are the possible outputs, where
 * `offset` indicates the position of the key in the key array:
 *
 *  - `__Map_Find_Default` returns:
 *    - `-1` if not found.
 *    - `offset` if found.
 *  - `__Map_Find_Offset` returns
 *    - `offset` if not found.
 *    - `offset` if found.
 *
 * This funcion shall handle hash collisions using the linear probing technique, which
 * consists in keep looking ahead in the key array until an empty spot is found or the
 * number of iterations reaches the map capacity. */
{
  uint16 key_size = map_fat_ptr->config.key_size;
  uint64 capacity = map_fat_ptr->capacity;
  uint64 capped_hash = key_hash % capacity;
  bool (*compare)(void*, void*) = map_fat_ptr->config.compare;

  uint64 iter = 0;
  uint64 offset = capped_hash;
  uint64 max_iter = capacity;

  byte* keys = map_fat_ptr->keys;
  byte* current_key_address = keys + (offset * key_size);
  enum __map_key_status current_key_status = map_fat_ptr->statuses[offset];

search:
  /* The key has never been used, stops the search immediately. */
  if (current_key_status == __Map__Key_Status__Not_Used)
    goto not_found;
  /* The key has been deleted, continue searching. */
  if (current_key_status == __Map__Key_Status__Deleted)
    goto next;

  /* The current key is present, compares it with the provided key. */
  if (compare(key_address, current_key_address))
    goto found;

next:
  iter++;
  offset++;

  /* Starts again from the beginning of the key array if the end was reached. */
  if (offset >= capacity)
    offset = 0;
  /* Stops the search if more iterations than the map capacity have been done. */
  if (iter > max_iter)
    goto not_found;

  /* Searches the next key. */
  current_key_address = keys + (offset * key_size);
  current_key_status = map_fat_ptr->statuses[offset];
  goto search;

not_found:
  switch (find_output) {
  case __Map_Find_Offset:
    return offset;
  default:
    return -1;
  }
found:
  return offset;
}