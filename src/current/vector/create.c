void vector_create (
    struct vector* vector
)
/**
 * This function shall allocate the provided vector. */
{
  u64 initial_capacity = next_pow2(vector->capacity);
  if (initial_capacity < VECTOR_DEFAULT_CAPACITY)
    initial_capacity = VECTOR_DEFAULT_CAPACITY;
  vector->capacity = initial_capacity;

  struct arena* arena = vector->arena;

  if (arena == NULL)
    goto allocate_elements;

  size footprint = (initial_capacity * sizeof(struct vector_element));

  if (vector->flags & Vector_Flag__Copy_Elements)
    footprint += (initial_capacity * vector->element_size);

  arena_prealloc(arena, footprint);

allocate_elements:
  vector->elements = arena_calloc(
    arena, initial_capacity, sizeof(struct vector_element));
}
