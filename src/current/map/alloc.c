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

  if (arena == NULL)
    goto set_capacity_and_alloc;

  fprintf(stderr, "arena!!\n");

set_capacity_and_alloc:
  fprintf(stderr, "alloc %li\n", initial_capacity);
  map->capacity = initial_capacity;
  map->buckets = arena_calloc(arena, initial_capacity, sizeof(struct map_entry*));
}
