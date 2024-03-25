void* vector_pop (
    Vector* vector
)
{
  if (vector->flags & VECTOR_FLAG__READ_ONLY)
    return NULL;

  if (vector->length == 0)
    return NULL;

  void* element = vector_get(vector, vector->length);
  vector->length--;

  return element;
}
