void* vector_get (
    struct vector* vector,
    u64 position
)
{
  struct vector_element* element = vector_element_get(vector, position);

  if (element == NULL)
    return NULL;

  return element->value;
}
