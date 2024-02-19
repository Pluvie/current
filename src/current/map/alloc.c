void map_alloc (
    struct map* map
)
/**
 * This function shall allocate the provided map. */
{
  size initial_capacity = next_pow2(map->capacity);
  if (initial_capacity < MAP_DEFAULT_CAPACITY)
    initial_capacity = MAP_DEFAULT_CAPACITY;

  struct arena* arena = map->arena;

  if ((d64) map->capacity / (d64) initial_capacity >= MAP_MAXIMUM_LOAD_FACTOR)
    initial_capacity *= 2;

  map->capacity = initial_capacity;

  if (arena == NULL)
    goto alloc_buckets_only;

  size footprint =
    (initial_capacity * sizeof(struct map_entry*)) +
    (initial_capacity * sizeof(struct map_entry));

  if (map->flags & Map_Flag__Copy_Keys)
    footprint += (initial_capacity * map->key_size);
  if (map->flags & Map_Flag__Copy_Values)
    footprint += (initial_capacity * map->value_size);

  arena_prealloc(arena, footprint);

alloc_buckets_only:
  map->buckets = arena_calloc(arena, initial_capacity, sizeof(struct map_entry*));
}
