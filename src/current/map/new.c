/**
 * This function shall create a new map using the provided arguments:
 *
 *  - *initial_capacity*: the initial capacity of the map; this is useful to
 *    reduce expensive rehashes if the amount of data the map must hold is
 *    known, even rougly, beforehand.
 *  - *key_size*: the amount of bytes occupied by a map key.
 *  - *value_size*: the amount of bytes occupied by a map value.
 *  - *hash_function*: the hash function the map must use to calculate the hash
 *    of a given key.
 *  - *compare_function*: the compare function the map must use to determine if two
 *    keys are equal.
 *
 * All these arguments are usually automatically calculated by the macro #map_new
 * or #map_new_cap. */
void* __map_new (
    uint32 initial_capacity,
    uint32 key_size,
    uint32 value_size,
    uint32 (*hash_function)(void*),
    bool (*compare_function)(void*, void*)
)
{
  struct __map_data* data = calloc(1,
    map_datasize + value_size + (value_size * initial_capacity));
  data->length = 0;
  data->capacity = initial_capacity;
  data->key_size = key_size;
  data->value_size = value_size;
  data->keys = calloc(1, key_size * initial_capacity);
  data->usage = calloc(1, sizeof(bool) * initial_capacity);
  data->hashes = calloc(1, sizeof(uint32) * initial_capacity);
  data->hash = hash_function;
  data->compare = compare_function;

  /* Fat pointer technique. The returned pointer is offsetted by a precise amount,
   * in order to store the map data and zero value.
   *
   * When allocating all the memory used by the map, it is firstly allocated an
   * amount of needed for the map data -- equal to `sizeof(struct __map_data)`,
   * then an amount needed to hold the map zero value -- equal to the `value_size`,
   * and lastly an amount needed to hold the actual map values -- equal to
   * `value_size * initial_capacity`.
   *
   * ```
   * ┌────────────────────┐
   * │                    │ <---- the allocation starts here
   * │     TABLE DATA     │
   * │                    │
   * ├────────────────────┤
   * │░░░░░ZERO░VALUE░░░░░│
   * ├────────────────────┤
   * │      value 0       │ <---- the returned pointer is here
   * │ ────────────────── │
   * │      value 1       │
   * │ ────────────────── │
   * │      value 2       │
   * │ ────────────────── │
   * │         .          │
   * │         .          │
   * │         .          │
   * │         v          │
   * │                    │
   * └────────────────────┘
   * ```
   *
   * The returned pointer starts in this last memory region. When it is passed around
   * in all the map operations and functions, it is always possible to retrieve the
   * pointer to the map data by going back to the known amount of bytes. */
  return ((byte*) data + map_datasize + value_size);
}
