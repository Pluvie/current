struct map* map_new (
    size key_size,
    size value_size,
    size initial_capacity
)
/**
 * This function shall create a new empty map. */
{
  struct map* map_ptr = calloc(1, sizeof(struct map));
  map_ptr->key_size = key_size;
  map_ptr->value_size = value_size;
  map_ptr->capacity = initial_capacity;
  map_ptr->buckets = calloc(initial_capacity, sizeof(struct map_entry*));
  map_ptr->hash = map_generic_hash;
  map_ptr->compare = map_generic_compare;

  return map_ptr;
}
