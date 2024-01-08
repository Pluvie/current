void* __map_new (
    struct __map_config config
)
/**
 * This function shall create a new map using the provided configuration options. */
{
  uint64 key_size = config.key_size;
  uint64 value_size = config.value_size;
  uint64 initial_capacity = config.initial_capacity;
  struct __map_memsize memsize = __map_calc_memsize(
    key_size, value_size, initial_capacity);

  struct arena* arena = config.arena;
  uint64 capacity = memsize.capacity;
  uint64 footprint = memsize.footprint;
  if (arena != NULL)
    arena_prealloc(arena, footprint);

  struct __map_fp* map_fp = arena_calloc(arena, 1,
    sizeof(struct __map_fp) +   /* Map fp data. */
    value_size +                /* Zero value. */
    (capacity * value_size));   /* Values. */

  map_fp->length = 0;
  map_fp->capacity = capacity;
  map_fp->config = config;
  map_fp->keys = arena_calloc(arena, capacity, key_size);
  map_fp->statuses = arena_calloc(arena, capacity, sizeof(uint8));
  map_fp->hashes = arena_calloc(arena, capacity, sizeof(uint64));

  /* Fat pointer technique. The returned pointer is offsetted by a precise amount,
   * in order to store the map data and zero value.
   *
   * When allocating all the memory used by the map, it is firstly allocated an
   * amount of needed for the map data -- equal to `sizeof(struct __map_fp)`,
   * then an amount needed to hold the map zero value -- equal to the `value_size`,
   * and lastly an amount needed to hold the actual map values -- equal to
   * `value_size * capacity`.
   *
   * ```
   * ┌────────────────────┐
   * │                    │ <---- the allocation starts here
   * │     __MAP_FP       │
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
  return ((byte*) map_fp + sizeof(struct __map_fp) + value_size);
}
