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

  free(vector->elements);
}
