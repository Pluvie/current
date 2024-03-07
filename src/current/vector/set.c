bool vector_set (
    struct vector* vector,
    u64 position,
    void* value
)
{
  if (position >= vector->length)
    return false;

  struct vector_element* element = vector->elements + position;
  element->value = value;

  return true;
}
