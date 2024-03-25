bool vector_set (
    Vector* vector,
    u64 position,
    void* element
)
{
  if (vector->flags & VECTOR_FLAG__READ_ONLY)
    return false;

  if (position >= vector->length)
    return false;

  if (vector->flags & VECTOR_FLAG__COPY_ELEMENTS)
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
