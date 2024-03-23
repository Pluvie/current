void vector_create (
    Vector* vector
)
/**
 * This function shall allocate the provided vector. */
{
  u64 initial_capacity = next_pow2(vector->capacity);
  if (initial_capacity < VECTOR_DEFAULT_CAPACITY)
    initial_capacity = VECTOR_DEFAULT_CAPACITY;
  vector->capacity = initial_capacity;

  if (vector->flags & VECTOR_FLAG__COPY_ELEMENTS)
    vector->elements = arena_calloc(
      vector->arena, initial_capacity, vector->element_size);
  else
    vector->elements = arena_calloc(
      vector->arena, initial_capacity, sizeof(void*));
}
