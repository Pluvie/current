struct vector_element* vector_element_get (
    struct vector* vector,
    u64 position
)
{
  struct vector_element* element;

search:
  if (position >= vector->capacity)
    return NULL;

  element = vector->elements + position;
  if (element->used)
    return element;

  position++;
  goto search;
}
