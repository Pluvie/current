void vector_destroy (
    Vector* vector
)
/**
 * This function shall free the memory used by the vector and all its elements. */
{
  if (vector->flags & VECTOR_FLAG__READ_ONLY)
    return;

  vector->length = 0;

  if (vector->arena != NULL)
    return;

  if (vector->elements == NULL)
    return;

  free(vector->elements);
}
