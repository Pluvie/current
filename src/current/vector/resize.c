void vector_resize (
    struct vector* vector
)
{
  vector->capacity <<= 1;

  vector->elements = arena_realloc(vector->arena,
    vector->elements,
    vector->capacity * sizeof(struct vector_element));
}
