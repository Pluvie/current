void* vector_get (
    struct vector* vector,
    u64 position
)
{
  if (position >= vector->length)
    return NULL;

  struct vector_element* element = vector->elements + position;
  return element->value;
}
