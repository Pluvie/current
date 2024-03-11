void* vector_pop (
    struct vector* vector
)
{
  if (vector->length == 0)
    return NULL;

  void* element = vector_get(vector, vector->length);
  vector->length--;

  return element;
}
