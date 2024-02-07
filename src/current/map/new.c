struct map* map_new (
    size key_size,
    size value_size,
    struct map_parameters* init_params
)
/**
 * This function shall create a new empty map.
 *
 * The *init_params* struct allows to specify map parameters directly during
 * initialization. */
{
  size initial_capacity = MAP_DEFAULT_CAPACITY;
  struct arena* arena = NULL;
  u32 flags = Map_Flag__None;

  if (init_params != NULL) {
    initial_capacity = next_pow2(init_params->capacity);
    arena = init_params->arena;
    flags = init_params->flags;
  }

  if (initial_capacity < MAP_DEFAULT_CAPACITY)
    initial_capacity = MAP_DEFAULT_CAPACITY;

  struct map* map_ptr = arena_calloc(arena, 1, sizeof(struct map));
  map_ptr->arena = arena;
  map_ptr->key_size = key_size;
  map_ptr->value_size = value_size;
  map_ptr->capacity = initial_capacity;
  map_ptr->buckets = arena_calloc(arena, initial_capacity, sizeof(struct map_entry*));
  map_ptr->hash = map_generic_hash;
  map_ptr->compare = map_generic_compare;
  map_ptr->flags = flags;

  return map_ptr;
}
