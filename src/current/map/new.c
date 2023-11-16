void* __map_new (
    int64 initial_capacity,
    struct arena* arena,
    int64 key_size,
    int64 value_size
)
/**
 * This function shall create a new map using the provided arguments:
 *
 *  - *initial_capacity*: the initial capacity of the map; this is useful to
 *    reduce expensive rehashes if the amount of data the map must hold is
 *    known, even rougly, beforehand.
 *  - *key_size*: the amount of bytes occupied by a map key.
 *  - *value_size*: the amount of bytes occupied by a map value.
 *
 * All these arguments are usually automatically calculated by the macro #map_new
 * or #map_new_cap. */
{
  int64 map_bytesize = map_fp_size +
    value_size + /* Zero value. */
    (value_size * initial_capacity);
  struct __map_fp* map_fp = (arena == NULL)
    ? calloc(1, map_bytesize)
    : arena_calloc(arena, 1, map_bytesize);

  map_fp->arena = arena;
  map_fp->length = 0;
  map_fp->capacity = initial_capacity;
  map_fp->key_size = key_size;
  map_fp->value_size = value_size;
  map_fp->keys = (arena == NULL)
    ? calloc(1, key_size * initial_capacity)
    : arena_calloc(arena, 1, key_size * initial_capacity);
  map_fp->usage = (arena == NULL)
    ? calloc(1, sizeof(bool) * initial_capacity)
    : arena_calloc(arena, 1, sizeof(bool) * initial_capacity);
  map_fp->hashes = (arena == NULL)
    ? calloc(1, sizeof(uint64) * initial_capacity)
    : arena_calloc(arena, 1, sizeof(uint64) * initial_capacity);
  map_fp->hash = NULL;
  map_fp->compare = NULL;
  map_fp->copy_keys = false;
  map_fp->key_copy = NULL;
  map_fp->key_copy_fixed_length = key_size;
  map_fp->key_length = NULL;

  /* Fat pointer technique. The returned pointer is offsetted by a precise amount,
   * in order to store the map data and zero value.
   *
   * When allocating all the memory used by the map, it is firstly allocated an
   * amount of needed for the map data -- equal to `sizeof(struct __map_fp)`,
   * then an amount needed to hold the map zero value -- equal to the `value_size`,
   * and lastly an amount needed to hold the actual map values -- equal to
   * `value_size * initial_capacity`.
   *
   * ```
   * ┌────────────────────┐
   * │                    │ <---- the allocation starts here
   * │      MAP DATA      │
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
  return ((byte*) map_fp + map_fp_size + value_size);
}
