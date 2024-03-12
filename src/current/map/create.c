void map_create (
    struct map* map
)
/**
 * This function shall allocate the provided map. */
{
  size initial_capacity = next_pow2(map->capacity);
  if (initial_capacity < MAP_DEFAULT_CAPACITY)
    initial_capacity = MAP_DEFAULT_CAPACITY;

  struct arena* arena = map->arena;

  if ((initial_capacity > map->capacity) &&
      ((d64) map->capacity / (d64) initial_capacity >= MAP_MAXIMUM_LOAD_FACTOR))
    initial_capacity *= 2;

  map->capacity = initial_capacity;
  map->probe_limit = log2(map->capacity);
  u64 probed_capacity = map->capacity + map->probe_limit;

  if (arena == NULL)
    goto allocate;

  size footprint = (probed_capacity * sizeof(struct map_entry));

  if (map->flags & Map_Flag__Copy_Keys)
    footprint += (probed_capacity * map->key_size);
  if (map->flags & Map_Flag__Copy_Values)
    footprint += (probed_capacity * map->value_size);

  arena_prealloc(arena, footprint);

allocate:
  map->entries = arena_calloc(arena, probed_capacity, sizeof(struct map_entry));
}
