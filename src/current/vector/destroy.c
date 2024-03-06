void vector_destroy (
    struct vector* vector
)
/**
 * This function shall free the memory used by the vector and all its elements. */
{
  if (vector->arena != NULL)
    return;

  if (vector->elements == NULL)
    return;

  if (vector->flags & Vector_Flag__Copy_Elements)
    for (i64 i = 0; i < vector->capacity; i++)
      free(vector->elements[i].value);

  free(vector->elements);
}
