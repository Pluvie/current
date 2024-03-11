bool vector_set (
    struct vector* vector,
    u64 position,
    void* element
)
{
  if (position >= vector->length)
    return false;

  if (vector->flags & Vector_Flag__Copy_Elements)
    goto copy_by_size;

  void** elements = vector->elements;
  elements[position] = element;
  return true;

copy_by_size:
  size element_size = vector->element_size;
  byte* element_position =
    (byte*) vector->elements +
    (position * element_size);
  memcpy(element_position, element, element_size);
  return true;
}
