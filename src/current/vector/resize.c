void vector_resize (
    struct vector* vector
)
{
  vector->capacity <<= 1;

  if (vector->flags & Vector_Flag__Copy_Elements)
    goto resize_by_element_size;

  vector->elements = arena_realloc(
    vector->arena, vector->elements, vector->capacity * sizeof(void*));
  memset(((void**) vector->elements) + vector->length, '\0',
    (vector->capacity - vector->length) * sizeof(void*));
  return;

resize_by_element_size:
  size element_size = vector->element_size;

  vector->elements = arena_realloc(
    vector->arena, vector->elements, vector->capacity * element_size);
  memset(((byte*) vector->elements) + (vector->length * element_size), '\0',
    (vector->capacity - vector->length) * element_size);
}
