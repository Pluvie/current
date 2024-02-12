void map_alloc (
    struct map* map_ptr
)
/**
 * This function shall allocate the provided map. */
{
  size initial_capacity = next_pow2(map_ptr->capacity);
  if (initial_capacity < MAP_DEFAULT_CAPACITY)
    initial_capacity = MAP_DEFAULT_CAPACITY;

  struct arena* arena = map_ptr->arena;
  map_ptr->capacity = initial_capacity;
  map_ptr->buckets = arena_calloc(arena, initial_capacity, sizeof(struct map_entry*));
}
