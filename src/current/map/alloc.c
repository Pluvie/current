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
  map->capacity = initial_capacity;
  map->buckets = arena_calloc(arena, initial_capacity, sizeof(struct map_entry*));
}
